#pragma once
#include "Windows.h"

enum AppMsg
{
	kAM_InitOtherWndMsg = WM_APP + 10,	// ������ʼ����������
	kAM_ControlInit,					// �ؼ���ʼ��
	kAM_Update_Status,					// ˢ�¿ؼ�
	kAM_PopMenuClickMsg,				// ���ò˵���Ϣ
	kAM_ResetIPInfo,					// ���÷����Ip
	kAM_PTZ,							// ptz_wnd ����ĵ����Ϣ
};