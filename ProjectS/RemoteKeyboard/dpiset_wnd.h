#pragma once
#include "stdafx.h"

class DPISetWnd : public WindowImplBase
{
public:
	DPISetWnd(HWND pa_hwnd);
	~DPISetWnd();

	DECLARE_DUIWND_INFO(_T("DPISetWnd"), CS_DBLCLKS, _T("dpiset_wnd.xml"))

	BEGIN_DUINOTIFY_MAP(DPISetWnd)
		DUINOTIFY_TYPE_HANDLER(DUI_MSGTYPE_SELECTCHANGED, OnSelectChanged)
		DUINOTIFY_TYPE_HANDLER(DUI_MSGTYPE_CLICK, OnClickBtn)
	END_DUINOTIFY_MAP()

public:
	bool DoModal();
	virtual void InitWindow() override;

private:
	void OnSelectChanged(TNotifyUI& msg, bool& handled);
	void OnClickBtn(TNotifyUI& msg, bool& handled);

private:
	HWND pa_hwnd_;
};

