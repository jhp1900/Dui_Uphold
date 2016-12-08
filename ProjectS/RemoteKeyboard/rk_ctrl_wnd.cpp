#include "rk_ctrl_wnd.h"
#include "RemoteKeyBoardCtrl/RemoteKeyBoardCtrl_h.h"
#include "RemoteKeyBoardCtrl/RemoteKeyBoardCtrl_c.c"
#include "res_singleton.h"

#pragma comment(lib,"Rpcrt4.lib")

void __RPC_FAR* __RPC_USER midl_user_allocate(size_t len) {
	return(malloc(len));
}

void __RPC_USER midl_user_free(void __RPC_FAR *ptr) {
	free(ptr);
}

RKCtrlWnd::RKCtrlWnd(HWND pa_hwnd)
	: pa_hwnd_(pa_hwnd)
	, binding_hwnd_(nullptr)
	, binding_str_(0)
	, current_channel_(-1)
	, rbtn_down_(false)
	, lbtn_down_(false)
	, old_point_({ 0, 0 })
	, current_pushpin_(_T(""))
{
	for (int i = 4; i < 12; ++i) {
		TCHAR name[32];
		_stprintf_s(name, sizeof(name) / sizeof(TCHAR), _T("rkbc_%02d"), i);
		ch_names_.push_back(name);
	}
	InterlockedExchange(&check_running_, TRUE);	// 原子操作，给 check_running_ 赋值为 TRUE
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
	
	// 这里启动一个线程来初始化控件位置； 尝试过各种窗口初始化、发送消息、发送事件等方式，均失败，故使用多线程 
	ctrl_initpos_thread_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&RKCtrlWnd::ResetKeyPos, this)));
}

void RKCtrlWnd::InitWindow()
{
}

LRESULT RKCtrlWnd::OnUpdateStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandle)
{
	static bool _last_enabled = true;
	bool _enable = (wParam != 0);
	unsigned int _check_value = (unsigned int)(lParam);
	TCHAR name[32];

	if (_last_enabled != _enable) {
		_last_enabled = _enable;
		for (int i = 1;; ++i) {
			_stprintf_s(name, sizeof(name) / sizeof(TCHAR), _T("rkbc_%02d"), i);
			if (!EnableControl(name, _last_enabled))
				break;
		}
	}

	if (_last_enabled) {
		unsigned int _recode_status = _check_value & 0x3;
		unsigned int _ch_status = (_check_value >> 2) & 0xf;
		unsigned int _director_status = (_check_value >> 6) & 0x3;

		for (int i = 1; i < 14; ++i) {
			_stprintf_s(name, sizeof(name) / sizeof(TCHAR), _T("rkbc_%02d"), i);

			if (i < 4) {
				EnableControl(name, _recode_status != i);
			} else if (i < 12) {
				EnableControl(name, _ch_status != i - 3);
			} else {
				EnableControl(name, _director_status != i - 11);
			}
		}
	}

	return LRESULT();
}

LRESULT RKCtrlWnd::OnCursorRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	bHandled = false;
	POINT point;
	point.x = GET_X_LPARAM(lParam);
	point.y = GET_Y_LPARAM(lParam);
	for (int i = 0; i < 8; ++i) {
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
	m_pm.FindControl(_T("control_panel"))->SetVisible(true);
	m_pm.FindControl(_T("sysn_panel"))->SetVisible(true);
	ctrl_initpos_thread_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&RKCtrlWnd::ResetKeyPos, this)));
}

void RKCtrlWnd::OnClickClosePanelBtn(TNotifyUI & msg, bool & handled)
{
	msg.pSender->GetParent()->SetVisible(false);
	ctrl_initpos_thread_ = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&RKCtrlWnd::ResetKeyPos, this)));
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
		::MessageBox(m_hWnd, _T("Address is empty or incorrectly set!"), _T("OnInit"), MB_OK);
		return false;
	}

	/*  绑定操作  */
	if (RpcStringBindingCompose(NULL, (RPC_WSTR)_T("ncacn_ip_tcp"), (RPC_WSTR)(LPTSTR)(LPCTSTR)(ip),
		(RPC_WSTR)(LPTSTR)(LPCTSTR)(port), NULL, &binding_str_) != RPC_S_OK
		|| RpcBindingFromStringBinding(binding_str_, &binding_hwnd_) != RPC_S_OK)
	{
		TCHAR buf[512];
		_stprintf_s(buf, sizeof(buf) / sizeof(TCHAR), _T("Connect the controlled terminal failed : %d"), GetLastError());
		::MessageBox(m_hWnd, buf, _T("OnInit"), MB_OK);
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
	for (int i = 0; i < 8; ++i) {
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
