#pragma once
#include "stdafx.h"
#include "msg_head.h"
#include <boost\crc.hpp>
#include <boost\thread.hpp>
#include "menu_wnd.h"
#include "ptz_wnd.h"

class RKCtrlWnd : public WindowImplBase
{
public:
	RKCtrlWnd(HWND pa_hwnd);
	~RKCtrlWnd();

	DECLARE_DUIWND_INFO(_T("RKCtrlWnd"), CS_DBLCLKS, _T("rk_ctrl_wnd.xml"))

	BEGIN_DUIMSG_MAP(RKCtrlWnd)
		DUIMSG_HANDLER(kAM_Update_Status, OnUpdateStatus)
		DUIMSG_HANDLER(WM_RBUTTONDOWN, OnCursorRButtonDown)
		DUIMSG_HANDLER(WM_RBUTTONUP, OnCursorRButtonUp)
		DUIMSG_HANDLER(WM_MOUSEMOVE, OnCursorMove)
		DUIMSG_HANDLER(WM_LBUTTONDOWN, OnPushpinLButtonDown)
		DUIMSG_HANDLER(WM_LBUTTONUP, OnPushpinLButtonUp)
		DUIMSG_HANDLER(kAM_PopMenuClickMsg, OnPopMenuClickMsg)
		DUIMSG_HANDLER(kAM_ResetIPInfo, OnResetIPInfoMsg)
		DUIMSG_HANDLER(kAM_PTZ, OnPtzClickMsg)
		DUIMSG_HANDLER(kAM_RecordStatusMsg, OnStatusShowkMsg)
		DUIMSG_HANDLER(kAM_DirectorStatusMsg, OnStatusShowkMsg)
	END_DUIMSG_MAP()

	BEGIN_DUINOTIFY_MAP(RKCtrlWnd)
		DUINOTIFY_HANDLER(_T("setupbtn"), DUI_MSGTYPE_CLICK, OnClickSetupBtn)
		DUINOTIFY_HANDLER(_T("close_panel"), DUI_MSGTYPE_CLICK, OnClickClosePanelBtn)
		DUINOTIFY_TYPE_HANDLER(DUI_MSGTYPE_CLICK, OnClick)
	END_DUINOTIFY_MAP()

public:
	void Init();

private:
	virtual void InitWindow() override;

private:
	LRESULT OnUpdateStatus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandle);
	LRESULT OnCursorRButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnCursorRButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnCursorMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnPushpinLButtonDown(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnPushpinLButtonUp(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnPopMenuClickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnResetIPInfoMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnPtzClickMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandle);
	LRESULT OnStatusShowkMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandle);

	void OnClick(TNotifyUI& msg, bool& handled);
	void OnClickSetupBtn(TNotifyUI& msg, bool& handled);
	void OnClickClosePanelBtn(TNotifyUI& msg, bool& handled);

private:
	bool EnableControl(LPCTSTR name, bool enable);
	void OnCheck();
	bool BindServerIP();
	void ResetKeyPos();
	bool InBtnRect(LPCTSTR btn_name, POINT point);
	void SetPanelVisible(LPCTSTR panel_name, bool visible);

private:
	HWND pa_hwnd_;

	vector<CDuiString> ch_names_;
	boost::shared_ptr<boost::thread> check_thread_;
	boost::shared_ptr<boost::thread> ctrl_initpos_thread_;
	RPC_BINDING_HANDLE binding_hwnd_;
	RPC_WSTR binding_str_;
	volatile LONG check_running_;

	UINT current_channel_;
	bool rbtn_down_;
	bool lbtn_down_;
	POINT old_point_;
	CDuiString current_pushpin_;

	std::shared_ptr<MenuWnd> menu_wnd_;
	std::shared_ptr<PtzWnd> ptz_wnd_;
};

