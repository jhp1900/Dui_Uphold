#pragma once
#include "stdafx.h"

class MainWnd : public WindowImplBase
{
public:
	MainWnd();
	~MainWnd();

	DECLARE_DUIWND_INFO(_T("MainWnd"), CS_DBLCLKS, _T("DlgMain.xml"))

	BEGIN_DUINOTIFY_MAP(MainWnd)
		DUINOTIFY_TYPE_HANDLER(DUI_MSGTYPE_CLICK, OnClickBtn)
	END_DUINOTIFY_MAP()

public:
	virtual void InitWindow() override;

private:
	void OnClickBtn(TNotifyUI &msg, bool &handled);
	virtual LRESULT OnClose(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& bHandled);

private:
	void CreatMenu();
	std::map<CDuiString, bool> menu_check_info_;
	CMenuWnd * pMenu_;
};

