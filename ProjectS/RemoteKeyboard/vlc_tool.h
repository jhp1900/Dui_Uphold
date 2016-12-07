#pragma once
#include "stdafx.h"
#include "vlc/vlc.h"

class VLCTool
{
public:
	VLCTool();
	~VLCTool();

	bool Initial();
	bool SetPlayerWindows(HWND pa_hwnd);
	bool SetMediaSource(string media_name);
	bool StartPlay();
	void Destory();

private:
	libvlc_instance_t* tingfox_mediaplayer_instance_;
	libvlc_media_player_t* tingfox_mediaplayer_;
	libvlc_media_t* media_source_;
};

