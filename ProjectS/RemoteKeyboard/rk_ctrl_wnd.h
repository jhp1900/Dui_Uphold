#pragma once
#include "stdafx.h"
#include "msg_head.h"
#include <boost\crc.hpp>
#include <boost\thread.hpp>

class RKCtrlWnd : public WindowImplBase
{
public:
	RKCtrlWnd(HWND pa_hwnd);
	~RKCtrlWnd();

	DECLARE_DUIWND_INFO(_T("RKCtrlWnd"), CS_DBLCLKS, _T("rk_ctrl_wnd.xml"))

	BEGIN_DUIMSG_MAP(RKCtrlWnd)
		//DUIMSG_HANDLER(WM_RBUTTONDOWN, OnCursorRButtonDown)
		//DUIMSG_HANDLER(WM_RBUTTONUP, OnCursorRButtonUp)
		//DUIMSG_HANDLER(WM_MOUSEMOVE, OnCursorMove)
		DUIMSG_HANDLER(kAM_ControlInit, OnInitCtrl)
		DUIMSG_HANDLER(kAM_Update_Status, OnUpdateStatus)
	END_DUIMSG_MAP()

	BEGIN_DUINOTIFY_MAP(RKCtrlWnd)
		DUINOTIFY_HANDLER(_T("setupbtn"), DUI_MSGTYPE_CLICK, OnClickSetupBtn)
		DUINOTIFY_TYPE_HANDLER(DUI_MSGTYPE_CLICK, OnClick)
	END_DUINOTIFY_MAP()

public:
	void Init();

private:
	LRESULT OnInitCtrl(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandle);
	LRESULT OnUpdateStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandle);

	void OnClickSetupBtn(TNotifyUI& msg, bool& handled);
	void OnClick(TNotifyUI& msg, bool& handled);

private:
	bool EnableControl(LPCTSTR name, bool enable);
	void OnCheck();
	bool BindServerIP();
	void ResetKeyPos();

private:
	HWND pa_hwnd_;

	boost::shared_ptr<boost::thread> m_check_thread;
	RPC_BINDING_HANDLE binding_hwnd_;
	RPC_WSTR binding_str_;
	volatile LONG check_running_;
};

