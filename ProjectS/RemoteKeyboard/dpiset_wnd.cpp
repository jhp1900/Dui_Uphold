#include "dpiset_wnd.h"
#include "msg_head.h"

DPISetWnd::DPISetWnd(HWND pa_hwnd)
	: pa_hwnd_(pa_hwnd)
{
}

DPISetWnd::~DPISetWnd()
{
}

bool DPISetWnd::DoModal()
{
	if (!Create(pa_hwnd_, _T(""), WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_ACCEPTFILES))
		return false;
	CenterWindow();
	return ShowModal() != 0;
}

void DPISetWnd::InitWindow()
{
}

void DPISetWnd::OnSelectChanged(TNotifyUI & msg, bool & handled)
{
	::PostMessage(pa_hwnd_, kAM_DPISetMsg, (WPARAM)_tstoi(msg.pSender->GetUserData()), 0);
}

void DPISetWnd::OnClickBtn(TNotifyUI & msg, bool & handled)
{
	Close(0);
}
