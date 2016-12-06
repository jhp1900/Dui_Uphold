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
	if(MessageBox(m_hWnd, _T("�˳�����"), _T("Message"), MB_OKCANCEL) == IDOK)
		exit(0);
	else 
		static_cast<CAnimationTabLayoutUI*>(m_pm.FindControl(_T("stepTabLayout")))->SelectItem(0);
	return LRESULT();
}

void MainWnd::OnClickBtn(TNotifyUI &msg, bool &handled)
{
	CDuiString name = msg.pSender->GetName();
	if (name == _T("closebtn"))
		Close();
	else if (name == _T("BtnOneClick"))
		static_cast<CAnimationTabLayoutUI*>(m_pm.FindControl(_T("stepTabLayout")))->SelectItem(1);
	else if (name == _T("DPI_100"))
		m_pm.SetDPI(96);
	else if (name == _T("DPI_125"))
		m_pm.SetDPI(120);
	else if (name == _T("DPI_150"))
		m_pm.SetDPI(144);
	else if (name == _T("DPI_175"))
		m_pm.SetDPI(168);
	else if (name == _T("DPI_200"))
		m_pm.SetDPI(192);
}
