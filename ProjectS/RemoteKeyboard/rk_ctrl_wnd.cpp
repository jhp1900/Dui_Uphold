#include "rk_ctrl_wnd.h"
#include "RemoteKeyBoardCtrl/RemoteKeyBoardCtrl_h.h"
#include "RemoteKeyBoardCtrl/RemoteKeyBoardCtrl_c.c"
#include "res_singleton.h"
#include "ip_set_wnd.h"

#pragma comment(lib,"Rpcrt4.lib")

static const struct {
	LPCTSTR name;
	LPCTSTR attr;
} g_LessionMappingTable[] = {
	{ _T("grade_edit"), _T("grade") },
	{ _T("teacher_id_edit"), _T("teacher_id") },
	{ _T("teacher_name_edit"), _T("teacher_name") },
	{ _T("subject_edit"), _T("subject") },
	{ _T("chapter_edit"), _T("chapter") },
	{ _T("chapter_name_edit"), _T("chapter_name") }
};

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len) {
	return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR *ptr) {
	free(ptr);
}

RKCtrlWnd::RKCtrlWnd(HWND pa_hwnd)
	: pa_hwnd_(pa_hwnd)
	, check_thread_(nullptr)
	, ctrl_initpos_thread_(nullptr)
	, binding_hwnd_(nullptr)
	, binding_str_(0)
	, current_channel_(-1)
	, rbtn_down_(false)
	, lbtn_down_(false)
	, old_point_({ 0, 0 })
	, current_pushpin_(_T(""))
	, menu_wnd_(nullptr)
	, ptz_wnd_(nullptr)
{
	for (int i = 0; i < 14; ++i) {
		TCHAR name[32];
		_stprintf_s(name, sizeof(name) / sizeof(TCHAR), _T("rkbc_%02d"), i);
		ch_names_.push_back(name);
	}
	InterlockedExchange(&check_running_, TRUE);	// ԭ�Ӳ������� check_running_ ��ֵΪ TRUE
}

RKCtrlWnd::~RKCtrlWnd()
{
}

void RKCtrlWnd::Init()
{
	RECT sys_rect;
	GetWindowRect(pa_hwnd_, &sys_rect);
	Create(pa_hwnd_, _T(""), UI_WNDSTYLE_FRAME, 0L, sys_rect);
	CenterWindow();
	ShowWindow(m_hWnd, SW_SHOW);
	
	BindServerIP();
	SendMessage(kAM_Update_Status, WPARAM(false), LPARAM(0));
	check_thread_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&RKCtrlWnd::OnCheck, this)));
	
	// ��������һ���߳�����ʼ���ؼ�λ�ã� ���Թ����ִ��ڳ�ʼ����������Ϣ�������¼��ȷ�ʽ����ʧ�ܣ���ʹ�ö��߳� 
	ctrl_initpos_thread_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&RKCtrlWnd::ResetKeyPos, this)));
}

void RKCtrlWnd::InitWindow()
{
	menu_wnd_.reset(new MenuWnd(m_hWnd));
	menu_wnd_->CreateWithDefaltStyle();
}

LRESULT RKCtrlWnd::OnUpdateStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandle)
{
	static bool _last_enabled = true;
	bool _enable = (wParam != 0);
	unsigned int _check_value = (unsigned int)(lParam);

	if (_last_enabled != _enable) {
		_last_enabled = _enable;
		for (int i = 1; i < 14; ++i) {
			if (!EnableControl(ch_names_[i], _last_enabled))
				break;
		}
	}

	if (_last_enabled) {
		unsigned int _recode_status = _check_value & 0x3;
		unsigned int _ch_status = (_check_value >> 2) & 0xf;
		unsigned int _director_status = (_check_value >> 6) & 0x3;

		for (int i = 1; i < 14; ++i) {
			if (i < 4) {
				EnableControl(ch_names_[i], _recode_status != i);
				PostMessage(kAM_RecordStatusMsg, (WPARAM)ch_names_[i].GetData(), _recode_status != i);
			} else if (i < 12) {
				EnableControl(ch_names_[i], _ch_status != i - 3);
			} else {
				EnableControl(ch_names_[i], _director_status != i - 11);
				PostMessage(kAM_DirectorStatusMsg, (WPARAM)ch_names_[i].GetData(), _director_status != i - 11);
			}
		}
	}

	/* ���ͬ���ſν��治������ʾ״̬����ˢ�� */
	if (!m_pm.FindControl(_T("sysn_panel"))->IsVisible())
		return 0;

	auto _GetExtendInfoWrap = [this](byte* &pBuf, long &nSize) -> boolean {
		boolean ret = false;

		RpcTryExcept
			ret = rkbc_GetExtendInfo(binding_hwnd_, kExtendType_LessionInfo, __int64(m_lession_info_checksum), &pBuf, &nSize);
		RpcExcept(1)
			ret = false;
		RpcEndExcept

			return ret;
	};

	byte *pBuf = 0;
	long nSize = 0;
	if (_enable && _GetExtendInfoWrap(pBuf, nSize) && pBuf) {
		auto const &items = g_LessionMappingTable;

		pugi::xml_document doc;
		if (doc.load(LPCTSTR(pBuf))) {
			pugi::xml_node elem = doc.child(_T("lesson"));
			if (elem) {
				for (int i = 0; i < _countof(items); ++i) {
					DuiLib::CControlUI *ctrl;
					if (ctrl = m_pm.FindControl(items[i].name))
						ctrl->SetText(elem.attribute(items[i].attr).as_string());
				}

				m_lession_info = LPCTSTR(pBuf);
				boost::crc_32_type result;
				result.process_bytes(reinterpret_cast<const byte *>(m_lession_info.data()), (m_lession_info.size() + 1) * sizeof(wchar_t));
				m_lession_info_checksum = result.checksum();
			}
		}
		midl_user_free(pBuf);
	}

	return LRESULT();
}

LRESULT RKCtrlWnd::OnCursorRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = false;
	POINT point;
	point.x = GET_X_LPARAM(lParam);
	point.y = GET_Y_LPARAM(lParam);
	for (int i = 4; i < 12; ++i) {
		if (InBtnRect(ch_names_[i], point)) {
			rbtn_down_ = true;
			current_channel_ = i;
			old_point_ = point;
			return 0;
		}
	}
	return LRESULT();
}

LRESULT RKCtrlWnd::OnCursorRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = false;
	if (-1 == current_channel_)
		return 0;

	ResSingleton::GetInstance()->GetSysCfg()->SetChBtnPos(
		ch_names_[current_channel_], m_pm.FindControl(ch_names_[current_channel_])->GetPos());
	current_channel_ = -1;
	rbtn_down_ = false;
	return LRESULT();
}

LRESULT RKCtrlWnd::OnCursorMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	auto movectrl = [&](CControlUI *ctrl) {
		RECT rect = ctrl->GetPos();
		int add_x = GET_X_LPARAM(lParam) - old_point_.x;
		int add_y = GET_Y_LPARAM(lParam) - old_point_.y;
		old_point_.x = GET_X_LPARAM(lParam);
		old_point_.y = GET_Y_LPARAM(lParam);
		rect.left += add_x;
		rect.right += add_x;
		rect.top += add_y;
		rect.bottom += add_y;
		ctrl->SetPos(rect);
	};

	if (rbtn_down_)
		movectrl(m_pm.FindControl(ch_names_[current_channel_]));
	else if (lbtn_down_)
		movectrl(m_pm.FindControl(current_pushpin_)->GetParent());

	return LRESULT();
}

LRESULT RKCtrlWnd::OnPushpinLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = false;
	POINT point;
	point.x = GET_X_LPARAM(lParam);
	point.y = GET_Y_LPARAM(lParam);

	auto lbtndow = [&](LPCTSTR pushpin) {
		lbtn_down_ = true;
		current_pushpin_ = pushpin;
		old_point_ = point;
	};

	if (InBtnRect(_T("pushpin_control"), point)) 
		lbtndow(_T("pushpin_control"));
	else if (InBtnRect(_T("pushpin_sysn"), point)) 
		lbtndow(_T("pushpin_sysn"));

	return LRESULT();
}

LRESULT RKCtrlWnd::OnPushpinLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = false;
	current_pushpin_ = _T("");
	lbtn_down_ = false;
	return LRESULT();
}

LRESULT RKCtrlWnd::OnPopMenuClickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	switch (wParam)
	{
		case SysnSchedule: {
			SetPanelVisible(_T("sysn_panel"), true);
			break;
		}
		case PTZ: {
			ptz_wnd_.reset(new PtzWnd(m_hWnd));
			ptz_wnd_->DoModal();
			break;
		}
		case ControlPanel: {
			SetPanelVisible(_T("control_panel"), true);
			break;
		}
		case LinkServe: {
			IpSetWnd ipset_wnd(m_hWnd, ServerIP);
			ipset_wnd.DoModal();
			break;
		}
		case BackStreams: {
			IpSetWnd ipset_wnd(m_hWnd, BackStreamsIP);
			ipset_wnd.DoModal();
			break;
		}

		default:
			break;
	}
	return LRESULT();
}

LRESULT RKCtrlWnd::OnResetIPInfoMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	if(wParam == ServerIP)
		BindServerIP();
	else if(wParam == BackStreamsIP)
		::PostMessage(pa_hwnd_, uMsg, wParam, lParam);
	return LRESULT();
}

LRESULT RKCtrlWnd::OnPtzClickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandle)
{
	CButtonUI * ptz_btn = static_cast<CButtonUI*>(m_pm.FindControl((LPCTSTR)wParam));
	if (ptz_btn)
		m_pm.SendNotify(ptz_btn, DUI_MSGTYPE_CLICK);
	return LRESULT();
}

LRESULT RKCtrlWnd::OnStatusShowkMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandle)
{
	if (lParam)
		return 0;
	CDuiString name = (LPCTSTR)wParam;
	if (uMsg == kAM_RecordStatusMsg) {
		COptionUI *record_status = static_cast<COptionUI*>(m_pm.FindControl(_T("record_status")));
		if (name == _T("rkbc_01")) {
			record_status->SetEnabled(false);
		} else if (name == _T("rkbc_02")) {
			record_status->SetEnabled(true);
			record_status->Selected(true);
		} else if (name == _T("rkbc_03")) {
			record_status->SetEnabled(true);
			record_status->Selected(false);
		}
	} else if (uMsg == kAM_DirectorStatusMsg) {
		if (name == _T("rkbc_12"))		// �Զ�����
			m_pm.FindControl(_T("director_status"))->SetEnabled(true);
		else if(name == _T("rkbc_13"))	// �ֶ�����
			m_pm.FindControl(_T("director_status"))->SetEnabled(false);
	}
	return LRESULT();
}

void RKCtrlWnd::OnClick(TNotifyUI & msg, bool & handled)
{
	int key = _tstoi(msg.pSender->GetUserData());
	if (key <= 0)
		return;

	unsigned __int64 _check_value = 0;
	bool _enable = true;

	RpcTryExcept
		_check_value = rkbc_KeyBoardCtrl(binding_hwnd_, key);
	RpcExcept(1)
		_enable = false;
	RpcEndExcept

	PostMessage(kAM_Update_Status, WPARAM(_enable), LPARAM(_check_value));
}

void RKCtrlWnd::OnClickSetupBtn(TNotifyUI & msg, bool & handled)
{
	LPPOINT lpoint = new tagPOINT;
	::GetCursorPos(lpoint);
	menu_wnd_->PopupWnd(lpoint);
}

void RKCtrlWnd::OnClickClosePanelBtn(TNotifyUI & msg, bool & handled)
{
	SetPanelVisible(msg.pSender->GetParent()->GetName(), false);
}

void RKCtrlWnd::OnClickSyncBtn(TNotifyUI & msg, bool & handled)
{
	auto const &items = g_LessionMappingTable;
	DuiLib::CControlUI *ctrl;

	if (msg.pSender->GetName() == _T("sync_ok")) {
		pugi::xml_document xmldoc;
		pugi::xml_node root = xmldoc.append_child(PUGIXML_TEXT("lesson"));

		for (int i = 0; i < _countof(items); ++i) {
			pugi::xml_attribute attr = root.append_attribute(items[i].attr);
			if (ctrl = m_pm.FindControl(items[i].name))
				attr = ctrl->GetText();
		}
		std::wostringstream oss;
		root.print(oss, L"", pugi::format_raw);

		auto _ExecuteExtendCmdWrap = [this](const std::wstring &buf) -> boolean {
			boolean ret = false;
			RpcTryExcept
				ret = rkbc_ExecuteExtendCmd(binding_hwnd_, kExtendType_LessionInfo, reinterpret_cast<const byte *>(buf.data()), (buf.size() + 1) * sizeof(wchar_t));
			RpcExcept(1)
				ret = false;
			RpcEndExcept

				return ret;
		};

		if (_ExecuteExtendCmdWrap(oss.str())) {
			m_lession_info = oss.str();

			boost::crc_32_type result;
			result.process_bytes(reinterpret_cast<const byte *>(m_lession_info.data()), (m_lession_info.size() + 1) * sizeof(wchar_t));
			m_lession_info_checksum = result.checksum();
		}
	}

	SetPanelVisible(_T("sysn_panel"), false);
}

bool RKCtrlWnd::EnableControl(LPCTSTR name, bool enable)
{
	CControlUI *ctrl = m_pm.FindControl(name);
	if (!ctrl)
		return false;

	if (ctrl->IsEnabled() != enable)
		ctrl->SetEnabled(enable);

	return true;
}

void RKCtrlWnd::OnCheck()
{
	while (check_running_)
	{
		unsigned __int64 _check_value = 0;
		bool _enable = true;

		RpcTryExcept
			_check_value = rkbc_GetStatus(binding_hwnd_);
		RpcExcept(1)
			_enable = false;
		RpcEndExcept

		if (!check_running_) break;

		PostMessage(kAM_Update_Status, WPARAM(_enable), LPARAM(_check_value));
		Sleep(1000);
	}
}

bool RKCtrlWnd::BindServerIP()
{
	CDuiString ip, port;
	ResSingleton::GetInstance()->GetSysCfg()->GetIpInfo(ServerIP, ip, port);
	if (ip.GetLength() < 7 || port.GetLength() < 1) {
		::MessageBox(m_hWnd, _T("Address is empty or incorrectly set!"), _T("InitWindow"), MB_OK);
		return false;
	}

	/*  �󶨲���  */
	if (RpcStringBindingCompose(NULL, (RPC_WSTR)_T("ncacn_ip_tcp"), (RPC_WSTR)(LPTSTR)(LPCTSTR)(ip),
		(RPC_WSTR)(LPTSTR)(LPCTSTR)(port), NULL, &binding_str_) != RPC_S_OK
		|| RpcBindingFromStringBinding(binding_str_, &binding_hwnd_) != RPC_S_OK)
	{
		TCHAR buf[512];
		_stprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Connect the controlled terminal failed : %d"), GetLastError());
		::MessageBox(m_hWnd, buf, _T("InitWindow"), MB_OK);
		return false;
	}
	return true;
}

void RKCtrlWnd::ResetKeyPos()
{
	Sleep(10);
	RECT pos = { 0 };
	CControlUI *ctrl;
	SysCfg *sys_cfg = ResSingleton::GetInstance()->GetSysCfg();
	for (int i = 4; i < 12; ++i) {
		pos = sys_cfg->GetChBtnPos(ch_names_[i], i, m_hWnd);
		ctrl = m_pm.FindControl(ch_names_[i]);
		ctrl->SetPos(pos, true);
	}
}

bool RKCtrlWnd::InBtnRect(LPCTSTR btn_name, POINT point)
{
	const RECT rect = m_pm.FindControl(btn_name)->GetPos();
	return PtInRect(&rect, point);
}

void RKCtrlWnd::SetPanelVisible(LPCTSTR panel_name, bool visible)
{
	m_pm.FindControl(panel_name)->SetVisible(visible);
	ctrl_initpos_thread_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&RKCtrlWnd::ResetKeyPos, this)));
}
