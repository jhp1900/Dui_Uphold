#include "back_wnd.h"
#include "res_singleton.h"

BackWnd::BackWnd()
{
}

BackWnd::~BackWnd()
{
}

void BackWnd::InitWindow()
{
	RunBackVideo();
	PostMessage(kAM_InitOtherWndMsg, 0, 0);
}

LRESULT BackWnd::OnInitOtherWndMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	rk_ctrl_wnd_.reset(new RKCtrlWnd(m_hWnd));
	rk_ctrl_wnd_->Init();
	return LRESULT();
}

LRESULT BackWnd::OnResetIPInfoMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandled)
{
	vlc_tool_->Destory();
	RunBackVideo();
	return LRESULT();
}

LRESULT BackWnd::OnDPISetMsg(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL & bHandle)
{
	m_pm.SetDPI((int)wParam);
	return LRESULT();
}

void BackWnd::RunBackVideo()
{
	char url[MAX_PATH] = { 0 };
	CDuiString str_url = _T("rtsp://");
	CDuiString ip, port;
	SysCfg *sys_cfg = ResSingleton::GetInstance()->GetSysCfg();
	sys_cfg->GetIpInfo(BackStreamsIP, ip, port);
	sys_cfg->WideToMulti(str_url + ip + _T("/") + port, url);

	vlc_tool_.reset(new VLCTool);
	if (!vlc_tool_->Initial())
		return;
	vlc_tool_->SetMediaSource(url);
	vlc_tool_->SetPlayerWindows(m_hWnd);
	vlc_tool_->StartPlay();
}

