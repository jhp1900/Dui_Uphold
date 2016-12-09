#pragma once
#include "stdafx.h"
#include "vlc_tool.h"
#include <memory>
#include "rk_ctrl_wnd.h"

class BackWnd : public WindowImplBase
{
public:
	BackWnd();
	~BackWnd();

	DECLARE_DUIWND_INFO(_T("BackWnd"), CS_DBLCLKS, _T("back_wnd.xml"))

	BEGIN_DUIMSG_MAP(BackWnd)
		DUIMSG_HANDLER(kAM_InitOtherWndMsg, OnInitOtherWndMsg)
		DUIMSG_HANDLER(kAM_ResetIPInfo, OnResetIPInfoMsg)
	END_DUIMSG_MAP()

public:
	virtual void InitWindow() override;

private:
	LRESULT OnInitOtherWndMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
	LRESULT OnResetIPInfoMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);

private:
	void RunBackVideo();

private:
	std::shared_ptr<VLCTool> vlc_tool_;
	std::shared_ptr<RKCtrlWnd> rk_ctrl_wnd_;
};

