#include "main_wnd.h"

MainWnd::MainWnd()
{
}

MainWnd::~MainWnd()
{
}

void MainWnd::InitWindow()
{
	//atablayout_ = static_cast<CAnimationTabLayoutUI*>(m_pm.FindControl(_T("BtnOneClick")));
}

LRESULT MainWnd::OnClose(UINT, WPARAM, LPARAM, BOOL & bHandled)
{
	if(MessageBox(m_hWnd, _T("ÍË³ö³ÌÐò"), _T("Message"), MB_OKCANCEL) == IDOK)
		exit(0);
	else 
		static_cast<CAnimationTabLayoutUI*>(m_pm.FindControl(_T("stepTabLayout")))->SelectItem(0);
	return LRESULT();
}

void MainWnd::OnClickBtn(TNotifyUI &msg, bool &handled)
{
	if (msg.pSender->GetName() == _T("closebtn"))
		Close();
	else if (msg.pSender->GetName() == _T("BtnOneClick"))
		static_cast<CAnimationTabLayoutUI*>(m_pm.FindControl(_T("stepTabLayout")))->SelectItem(1);
}
