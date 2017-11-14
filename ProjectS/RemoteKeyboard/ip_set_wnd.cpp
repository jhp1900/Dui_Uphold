#include "ip_set_wnd.h"
#include "msg_head.h"

IpSetWnd::IpSetWnd(HWND pa_hwnd, IPSourceType type)
	: pa_hwnd_(pa_hwnd)
	, ip_source_type_(type)
{
}

IpSetWnd::~IpSetWnd()
{
}

bool IpSetWnd::DoModal()
{
	if (!Create(pa_hwnd_, _T(""), WS_POPUP, WS_EX_TOOLWINDOW | WS_EX_ACCEPTFILES))
		return false;
	CenterWindow();
	OnLocalInit();
	return ShowModal() != 0;
}

void IpSetWnd::InitWindow()
{
	//SetWindowLong(m_hWnd, GWL_EXSTYLE, GetWindowLong(m_hWnd, GWL_EXSTYLE) | WS_EX_LAYERED);
	//// ÉèÖÃÍ¸Ã÷É«  		
	//COLORREF cr_key = RGB(0, 0, 0);
	//SetLayeredWindowAttributes(m_hWnd, cr_key, 0, LWA_COLORKEY);
	//SetLayeredWindowAttributes(m_hWnd, 0, 200, LWA_ALPHA);
}

void IpSetWnd::OnLocalInit()
{
  SysCfg *sys_cfg = ResSingleton::GetInstance()->GetSysCfg();

  if (ip_source_type_ == ServerIP) {
    m_pm.FindControl(L"ip_set_area")->SetVisible(true);
    CDuiString ip, port;
    sys_cfg->GetIpInfo(ip_source_type_, ip, port);
    m_pm.FindControl(_T("ip_edit"))->SetText(ip);
    m_pm.FindControl(_T("port_edit"))->SetText(port);
  }
  else if (ip_source_type_ == BackStreamsIP) {
    m_pm.FindControl(L"bk_url_area")->SetVisible(true);
    m_pm.FindControl(L"bk_url")->SetText(sys_cfg->GetBkUrl());
  }
}

void IpSetWnd::OnClickBtn(TNotifyUI & msg, bool & handled)
{
	if (msg.pSender->GetName() == _T("ok")) {
    if (ip_source_type_ == ServerIP) {
      WPARAM ip = (WPARAM)m_pm.FindControl(_T("ip_edit"))->GetText().GetData();
      LPARAM port = (LPARAM)m_pm.FindControl(_T("port_edit"))->GetText().GetData();
      ResSingleton::GetInstance()->GetSysCfg()->SetIpInfo(ip_source_type_, (LPCTSTR)ip, (LPCTSTR)port);
    }
    else if (ip_source_type_ == BackStreamsIP) {
      ResSingleton::GetInstance()->GetSysCfg()->SetBkUrl(m_pm.FindControl(_T("bk_url"))->GetText());
    }
		::PostMessage(pa_hwnd_, kAM_ResetIPInfo, ip_source_type_, 0);
	}

	Close(0);
}
