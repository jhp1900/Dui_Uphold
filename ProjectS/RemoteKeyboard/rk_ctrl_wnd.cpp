#include "rk_ctrl_wnd.h"
#include "RemoteKeyBoardCtrl/RemoteKeyBoardCtrl_h.h"
#include "RemoteKeyBoardCtrl/RemoteKeyBoardCtrl_c.c"

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
{
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
	
	ResetKeyPos();
	SendMessage(kAM_Update_Status, WPARAM(false), LPARAM(0));
	BindServerIP();
	m_check_thread = boost::shared_ptr<boost::thread>(new boost::thread(boost::bind(&RKCtrlWnd::OnCheck, this)));
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
	CDuiString ip = _T("127.0.0.1"), port = _T("12321");
	//ResSingleton::GetInstance()->GetSysCfg()->GetIpInfo(ServerIP, ip, port);
	//if (ip.GetLength() < 7 || port.GetLength() < 1) {
	//	::MessageBox(m_hWnd, _T("Address is empty or incorrectly set!"), _T("OnInit"), MB_OK);
	//	return false;
	//}

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
	RECT pos[8] = {};
	RECT win_rect = {};
	GetWindowRect(m_hWnd, &win_rect);
	UINT width_pitch = (win_rect.right - win_rect.left - 70) / 5;
	UINT height_pitch = (win_rect.bottom - win_rect.top - 50 - 27) / 3;

	for (int i = 0; i < 4; ++i) {
		pos[i].left = (i + 1) * width_pitch;
		pos[i].right = pos[i].left + 70;
		pos[i].top = height_pitch;
		pos[i].bottom = pos[i].top + 50;
	}
	for (int i = 4; i < 8; ++i) {
		pos[i].left = (i - 3) * width_pitch;
		pos[i].right = pos[i].left + 70;
		pos[i].top = height_pitch * 2;
		pos[i].bottom = pos[i].top + 50;
	}

	TCHAR name[32];
	CControlUI *ctrl;
	for (int i = 0; i < 8; ++i) {
		_stprintf_s(name, sizeof(name) / sizeof(TCHAR), _T("rkbc_%02d"), i + 4);
		ctrl = m_pm.FindControl(name);
		ctrl->SetPos(pos[i]);
	}
}
