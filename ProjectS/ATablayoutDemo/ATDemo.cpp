#include "stdafx.h"
#include "main_wnd.h"

//������ڴ����øú��������ڴ�й¶���
//�����˳�ǰ����_CrtDumpMemoryLeaks();�����ɲ鿴�ڴ�й¶��ID�ţ���ID�ſ���ΪBreakpoint�Ĳ���������ʱ��������Ӧλ���Զ��ϵ�
inline  void  EnableMemLeakCheck(int Breakpoint = 0) {
	_CrtSetDbgFlag(_CrtSetDbgFlag(_CRTDBG_REPORT_FLAG) | _CRTDBG_LEAK_CHECK_DF);
	if (Breakpoint)
		_CrtSetBreakAlloc(1912);
}

void InitResource()
{
	// ��Դ����
	CPaintManagerUI::SetResourceType(UILIB_FILE);
	// ��Դ·��
	CDuiString strResourcePath = CPaintManagerUI::GetInstancePath();
	// ������Դ
	switch (CPaintManagerUI::GetResourceType())
	{
		case UILIB_FILE:
		{
			strResourcePath += _T("skin\\ATablayoutDemo\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
			// ������Դ������
			CResourceManager::GetInstance()->LoadResource(_T("res.xml"), NULL);
			break;
		}
		case UILIB_RESOURCE:
		{
			strResourcePath += _T("skin\\ATablayoutDemo\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
			// ������Դ������
			CResourceManager::GetInstance()->LoadResource(_T("IDR_RES"), _T("xml"));
			break;
		}
		case UILIB_ZIP:
		{
			strResourcePath += _T("skin\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());
			CPaintManagerUI::SetResourceZip(_T("ATablayoutDemo.zip"), true);
			// ������Դ������
			CResourceManager::GetInstance()->LoadResource(_T("res.xml"), NULL);
			break;
		}
		case UILIB_ZIPRESOURCE:
		{
			strResourcePath += _T("skin\\ATablayoutDemo\\");
			CPaintManagerUI::SetResourcePath(strResourcePath.GetData());

			HRSRC hResource = ::FindResource(CPaintManagerUI::GetResourceDll(), _T("IDR_ZIPRES"), _T("ZIPRES"));
			if (hResource != NULL) {
				DWORD dwSize = 0;
				HGLOBAL hGlobal = ::LoadResource(CPaintManagerUI::GetResourceDll(), hResource);
				if (hGlobal != NULL) {
					dwSize = ::SizeofResource(CPaintManagerUI::GetResourceDll(), hResource);
					if (dwSize > 0) {
						CPaintManagerUI::SetResourceZip((LPBYTE)::LockResource(hGlobal), dwSize);
						// ������Դ������
						CResourceManager::GetInstance()->LoadResource(_T("res.xml"), NULL);
					}
				}
				::FreeResource(hResource);
			}
		}
		break;
	}
}

int APIENTRY _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	EnableMemLeakCheck();
	HRESULT Hr = ::CoInitialize(NULL);
	if (FAILED(Hr))
		return 0;

	CPaintManagerUI::SetInstance(hInstance);
	InitResource();

	MainWnd *main_wnd = new MainWnd();
	if (nullptr == main_wnd)
		return 0;
	main_wnd->Create(NULL, _T(""), UI_WNDSTYLE_FRAME, 0L, 0, 0, 900, 600);
	main_wnd->CenterWindow();
	::ShowWindow(*main_wnd, SW_SHOW);
	CPaintManagerUI::MessageLoop();

	::CoUninitialize();
	_CrtDumpMemoryLeaks();
	return 0;
}