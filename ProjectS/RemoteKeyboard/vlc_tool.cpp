#include "vlc_tool.h"

VLCTool::VLCTool()
	: tingfox_mediaplayer_instance_(nullptr)
	, tingfox_mediaplayer_(nullptr)
	, media_source_(nullptr)
{
}

VLCTool::~VLCTool()
{
}

bool VLCTool::Initial()
{
	return (tingfox_mediaplayer_instance_ = libvlc_new(0, NULL));
}

bool VLCTool::SetPlayerWindows(HWND pa_hwnd)
{
	if (!pa_hwnd)
		return false;
	else
		libvlc_media_player_set_hwnd(tingfox_mediaplayer_, pa_hwnd);

	return true;
}

bool VLCTool::SetMediaSource(string media_name)
{
	if (empty(media_name)) {
		return false;
	} else {
		media_source_ = libvlc_media_new_location(tingfox_mediaplayer_instance_, media_name.c_str());
		tingfox_mediaplayer_ = libvlc_media_player_new_from_media(media_source_);
		return true;
	}
}

bool VLCTool::StartPlay()
{
	if (!tingfox_mediaplayer_)
		return false;
	libvlc_media_player_play(tingfox_mediaplayer_);
	return true;
}

void VLCTool::Destory()
{
	libvlc_media_release(media_source_);
	libvlc_media_player_release(tingfox_mediaplayer_);
	libvlc_release(tingfox_mediaplayer_instance_);
}
