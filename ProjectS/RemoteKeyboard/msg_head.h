#pragma once
#include "Windows.h"

enum AppMsg
{
	kAM_InitOtherWndMsg = WM_APP + 10,	// 创建初始化其他窗体
	kAM_ControlInit,					// 控件初始化
	kAM_Update_Status,					// 刷新控件
	kAM_PopMenuClickMsg,				// 设置菜单消息
};