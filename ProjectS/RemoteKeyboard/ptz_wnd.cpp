#include "ptz_wnd.h"
#include "msg_head.h"

PtzWnd::PtzWnd(HWND pa_hwnd)
	: pa_hwnd_(pa_hwnd)
{
}

PtzWnd::~PtzWnd()
{
}

bool PtzWnd::DoModal()
{
	if (!Create(pa_hwnd_, _T(""), WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_ACCEPTFILES))
		return false;
	CenterWindow();
	return ShowModal() != 0;
}

void PtzWnd::InitWindow()
{
	SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	// ÉèÖÃÍ¸Ã÷É«  		
	COLORREF cr_key = RGB(0, 0, 0);
	SetLayeredWindowAttributes(m_hWnd, cr_key, 0, LWA_COLORKEY);
	SetLayeredWindowAttributes(m_hWnd, 0, 200, LWA_ALPHA);
}

void PtzWnd::OnClickBtn(TNotifyUI & msg, bool & handled)
{
	CDuiString name = msg.pSender->GetName();
	if (name == _T("close_ptz"))
		Close(0);
	else
		::PostMessage(pa_hwnd_, kAM_PTZ, (WPARAM)name.GetData(), 0);
}
