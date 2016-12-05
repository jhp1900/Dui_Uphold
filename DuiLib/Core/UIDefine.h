#pragma once

namespace DuiLib
{
#define MAX_FONT_ID		30000
#define CARET_TIMERID	0x1999

	// �б�����
	enum ListType
	{
		LT_LIST = 0,
		LT_COMBO,
		LT_TREE,
	};

	// ����궨��
#define DUI_ARROW           32512
#define DUI_IBEAM           32513
#define DUI_WAIT            32514
#define DUI_CROSS           32515
#define DUI_UPARROW         32516
#define DUI_SIZE            32640
#define DUI_ICON            32641
#define DUI_SIZENWSE        32642
#define DUI_SIZENESW        32643
#define DUI_SIZEWE          32644
#define DUI_SIZENS          32645
#define DUI_SIZEALL         32646
#define DUI_NO              32648
#define DUI_HAND            32649

	// ��Ϣ����
	enum DuiSig
	{
		DuiSig_end = 0, // [marks end of message map]
		DuiSig_lwl,     // LRESULT (WPARAM, LPARAM)
		DuiSig_vn,      // void (TNotifyUI)
	};

	// ���Ŀؼ�
	class CControlUI;

	// Structure for notifications to the outside world
	typedef struct tagTNotifyUI
	{
		CDuiString sType;
		CDuiString sVirtualWnd;
		CControlUI* pSender;
		DWORD dwTimestamp;
		POINT ptMouse;
		WPARAM wParam;
		LPARAM lParam;
	} TNotifyUI;

	class CNotifyPump;
	typedef void (CNotifyPump::*DUI_PMSG)(TNotifyUI& msg);  //ָ������

	union DuiMessageMapFunctions
	{
		DUI_PMSG pfn;   // generic member function pointer
		LRESULT(CNotifyPump::*pfn_Notify_lwl)(WPARAM, LPARAM);
		void (CNotifyPump::*pfn_Notify_vn)(TNotifyUI&);
	};

	//����������Ϣ����
	//////////////////////////////////////////////////////////////////////////

#define DUI_MSGTYPE_MENU                   (_T("menu"))
#define DUI_MSGTYPE_LINK                   (_T("link"))

#define DUI_MSGTYPE_TIMER                  (_T("timer"))
#define DUI_MSGTYPE_CLICK                  (_T("click"))
#define DUI_MSGTYPE_DBCLICK                (_T("dbclick"))

#define DUI_MSGTYPE_RETURN                 (_T("return"))
#define DUI_MSGTYPE_SCROLL                 (_T("scroll"))

#define DUI_MSGTYPE_DROPDOWN               (_T("dropdown"))
#define DUI_MSGTYPE_SETFOCUS               (_T("setfocus"))

#define DUI_MSGTYPE_KILLFOCUS              (_T("killfocus"))
#define DUI_MSGTYPE_ITEMCLICK 		   	   (_T("itemclick"))
#define DUI_MSGTYPE_ITEMRCLICK 			   (_T("itemrclick"))
#define DUI_MSGTYPE_TABSELECT              (_T("tabselect"))

#define DUI_MSGTYPE_ITEMSELECT 		   	   (_T("itemselect"))
#define DUI_MSGTYPE_ITEMEXPAND             (_T("itemexpand"))
#define DUI_MSGTYPE_WINDOWINIT             (_T("windowinit"))
#define DUI_MSGTYPE_WINDOWSIZE             (_T("windowsize"))
#define DUI_MSGTYPE_BUTTONDOWN 		   	   (_T("buttondown"))
#define DUI_MSGTYPE_MOUSEENTER			   (_T("mouseenter"))
#define DUI_MSGTYPE_MOUSELEAVE			   (_T("mouseleave"))

#define DUI_MSGTYPE_TEXTCHANGED            (_T("textchanged"))
#define DUI_MSGTYPE_HEADERCLICK            (_T("headerclick"))
#define DUI_MSGTYPE_ITEMDBCLICK            (_T("itemdbclick"))
#define DUI_MSGTYPE_SHOWACTIVEX            (_T("showactivex"))

#define DUI_MSGTYPE_ITEMCOLLAPSE           (_T("itemcollapse"))
#define DUI_MSGTYPE_ITEMACTIVATE           (_T("itemactivate"))
#define DUI_MSGTYPE_VALUECHANGED           (_T("valuechanged"))
#define DUI_MSGTYPE_VALUECHANGED_MOVE      (_T("movevaluechanged"))

#define DUI_MSGTYPE_SELECTCHANGED 		   (_T("selectchanged"))
#define DUI_MSGTYPE_UNSELECTED	 		   (_T("unselected"))

#define DUI_MSGTYPE_TREEITEMDBCLICK 		(_T("treeitemdbclick"))
#define DUI_MSGTYPE_CHECKCLICK				(_T("checkclick"))
#define DUI_MSGTYPE_TEXTROLLEND 			(_T("textrollend"))
#define DUI_MSGTYPE_COLORCHANGED		    (_T("colorchanged"))

#define DUI_MSGTYPE_LISTITEMSELECT 		   	(_T("listitemselect"))
#define DUI_MSGTYPE_LISTITEMCHECKED 		(_T("listitemchecked"))
#define DUI_MSGTYPE_COMBOITEMSELECT 		(_T("comboitemselect"))
#define DUI_MSGTYPE_LISTHEADERCLICK			(_T("listheaderclick"))
#define DUI_MSGTYPE_LISTHEADITEMCHECKED		(_T("listheaditemchecked"))
#define DUI_MSGTYPE_LISTPAGECHANGED			(_T("listpagechanged"))

	//////////////////////////////////////////////////////////////////////////

	struct DUI_MSGMAP_ENTRY;
	struct DUI_MSGMAP
	{
#ifndef UILIB_STATIC
		const DUI_MSGMAP* (PASCAL* pfnGetBaseMap)();
#else
		const DUI_MSGMAP* pBaseMap;
#endif
		const DUI_MSGMAP_ENTRY* lpEntries;
	};

	//�ṹ����
	struct DUI_MSGMAP_ENTRY //����һ���ṹ�壬�������Ϣ��Ϣ
	{
		CDuiString sMsgType;          // DUI��Ϣ����
		CDuiString sCtrlName;         // �ؼ�����
		UINT       nSig;              // ��Ǻ���ָ������
		DUI_PMSG   pfn;               // ָ������ָ��
	};

/*
 *	Declare dui window class **********************************************************************
 */

#define DECLARE_DUIWND_INFO(WndClassName, WndClassStyle, szXmlFileName) \
public: \
	LPCTSTR GetWindowClassName() const \
	{ \
		return WndClassName; \
	} \
	\
	UINT GetClassStyle() const \
	{ \
		return WndClassStyle; \
	} \
	DuiLib::CDuiString GetSkinFile() \
	{ \
	return (LPCTSTR)szXmlFileName; \
	}

 /*
  *	WindowImplBase::HandleCustomMessage map *******************************************************
  */

#define BEGIN_DUIMSG_MAP(theClass) \
public: \
	LRESULT HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) \
	{ \
		LRESULT lRes = 0;

 //	Handler prototypes:
 //  LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL &bHandled);
 //  LRESULT CommandHandler(WORD wNotifyCode, WORD wID, HWND hWndCtl, BOOL &bHandled);
 //  LRESULT NotifyHandler(int idCtrl, LPNMHDR pnmh, BOOL& bHandled);

#define DUIMSG_HANDLER(msg, func) \
		if ( uMsg == msg ) \
		{ \
			bHandled = TRUE; \
			lRes = func(uMsg, wParam, lParam, bHandled); \
			if( bHandled ) \
				return lRes; \
		}

#define DUIMSG_RANGE_HANDLER(msgFirst, msgLast, func) \
		if( uMsg >= msgFirst && uMsg <= msgLast ) \
		{ \
			bHandled = TRUE; \
			lRes = func(uMsg, wParam, lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_COMMAND_HANDLER(id, code, func) \
		if( uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam) ) \
		{ \
			bHandled = TRUE; \
			lRes = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
			if(bHandled) \
				return TRUE; \
		}

#define DUIMSG_COMMAND_ID_HANDLER(id, func) \
		if( uMsg == WM_COMMAND && id == LOWORD(wParam) ) \
		{ \
			bHandled = TRUE; \
			lRes = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_COMMAND_CODE_HANDLER(code, func) \
		if( uMsg == WM_COMMAND && code == HIWORD(wParam) ) \
		{ \
			bHandled = TRUE; \
			lRes = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_COMMAND_RANGE_HANDLER(idFirst, idLast, func) \
		if( uMsg == WM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast ) \
		{ \
			bHandled = TRUE; \
			lRes = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_COMMAND_RANGE_CODE_HANDLER(idFirst, idLast, code, func) \
		if( uMsg == WM_COMMAND && code == HIWORD(wParam) && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast ) \
		{ \
			bHandled = TRUE; \
			lRes = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_NOTIFY_HANDLER(id, cd, func) \
		if( uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom && cd == ((LPNMHDR)lParam)->code ) \
		{ \
			bHandled = TRUE; \
			lRes = func((int)wParam, (LPNMHDR)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_NOTIFY_ID_HANDLER(id, func) \
		if( uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom ) \
		{ \
			bHandled = TRUE; \
			lRes = func((int)wParam, (LPNMHDR)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_NOTIFY_CODE_HANDLER(cd, func) \
		if( uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code ) \
		{ \
			bHandled = TRUE; \
			lRes = func((int)wParam, (LPNMHDR)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_NOTIFY_RANGE_HANDLER(idFirst, idLast, func) \
		if( uMsg == WM_NOTIFY && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast ) \
		{ \
			bHandled = TRUE; \
			lRes = func((int)wParam, (LPNMHDR)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define DUIMSG_NOTIFY_RANGE_CODE_HANDLER(idFirst, idLast, cd, func) \
		if( uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast ) \
		{ \
			bHandled = TRUE; \
			lRes = func((int)wParam, (LPNMHDR)lParam, bHandled); \
			if( bHandled ) \
				return TRUE; \
		}

#define CHAIN_DUIMSG_MAP(theClass) \
		{ \
			lRes = theClass::HandleCustomMessage(uMsg, wParam, lParam, bHandled); \
			if( bHandled ) \
				return lRes; \
		}

#define END_DUIMSG_MAP() \
		bHandled = FALSE; \
		return 0; \
	}

#define DECLARE_EMPTY_DUIMSG_MAP() \
protected: \
	LRESULT HandleCustomMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled ) \
	{ \
		LRESULT lRes = 0; \
		bHandled = FALSE; \
		return 0; \
	}

/*
 *	Notify msg map ********************************************************************************
 */
#define BEGIN_DUINOTIFY_MAP(theClass) \
protected: \
	typedef DuiLib::TNotifyUI TNotifyUI; \
	\
	void Notify(TNotifyUI &msg) \
	{ \
        bool handled = true;

#define DUINOTIFY_HANDLER(CtrlName, NotifyType, func) \
    if (msg.pSender \
        && !msg.pSender->GetName().CompareNoCase(CtrlName) \
        && !msg.sType.CompareNoCase(NotifyType) \
        ) \
    { \
        func(msg, handled); \
        if (handled) \
            return; \
    }

#define DUINOTIFY_TYPE_HANDLER(NotifyType, func) \
	if (!msg.sType.CompareNoCase(NotifyType)) \
	{ \
		func(msg, handled); \
        if (handled) \
		    return; \
	}

#define BEGIN_DUINOTIFY_TYPE_HANDLER(NotifyType) \
	if (!msg.sType.CompareNoCase(NotifyType)) \
	{

//	Handler prototypes:
//  void NotifyHandler(TNotifyUI &msg, bool& handled);

#define DUINOTIFY_CONTROL_HANDLER(control, func) \
    if (msg.pSender == control) \
    { \
        func(msg, handled); \
        if (handled) \
            return; \
    }

#define DUINOTIFY_NAME_HANDLER(CtrlName, func) \
	if (!msg.pSender->GetName().CompareNoCase(CtrlName)) \
	{ \
		func(msg, handled); \
        if (handled) \
		    return; \
	}

#define END_DUINOTIFY_TYPE_HANDLER() \
        if (handled) \
		    return; \
	}

#define CHAIN_DUINOTIFY_MAP(theClass) \
    { \
        theClass::Notify(msg); \
    }

#define END_DUINOTIFY_MAP() \
	}

/*
 *	IDialogBuilderCallback::CreateControl map *****************************************************
 */

#define BEGIN_DUICONTROL_CREATE(theClass) \
	DuiLib::CControlUI* CreateControl(LPCTSTR pstrClass) \
	{ \
		DuiLib::CDuiString strClass(pstrClass);

#define DUICONTROL_CREATE(XmlTagName, UIClass) \
	if ( ! strClass.CompareNoCase(XmlTagName) ) \
		return ( new UIClass );

#define DUICONTROL_CREATE_FROM_XML(XmlTagName, XmlFile) \
    if ( ! strClass.CompareNoCase(XmlTagName) ) \
    { \
        DuiLib::CDialogBuilder builder; \
        DuiLib::CControlUI *pControl = builder.Create(XmlFile, NULL, this, &GetPaintManager()); \
        ASSERT(pControl != NULL && "DUICONTROL_CREATE_FROM_XML"); \
        return pControl; \
    }

#define END_DUICONTROL_CREATE() \
		return NULL; \
	}


	//����
#ifndef UILIB_STATIC
#define DUI_DECLARE_MESSAGE_MAP()                                         \
private:                                                                  \
	static const DUI_MSGMAP_ENTRY _messageEntries[];                      \
protected:                                                                \
	static const DUI_MSGMAP messageMap;                                   \
	static const DUI_MSGMAP* PASCAL _GetBaseMessageMap();                 \
	virtual const DUI_MSGMAP* GetMessageMap() const;                      \

#else
#define DUI_DECLARE_MESSAGE_MAP()                                         \
private:                                                                  \
	static const DUI_MSGMAP_ENTRY _messageEntries[];                      \
protected:                                                                \
	static  const DUI_MSGMAP messageMap;				                  \
	virtual const DUI_MSGMAP* GetMessageMap() const;                      \

#endif


	//����������ʼ
#ifndef UILIB_STATIC
#define DUI_BASE_BEGIN_MESSAGE_MAP(theClass)                              \
	const DUI_MSGMAP* PASCAL theClass::_GetBaseMessageMap()               \
	{ return NULL; }                                                  \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
	{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
	{  &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] };\
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#else
#define DUI_BASE_BEGIN_MESSAGE_MAP(theClass)                              \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
	{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
	{  NULL, &theClass::_messageEntries[0] };                         \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#endif


	//����������ʼ
#ifndef UILIB_STATIC
#define DUI_BEGIN_MESSAGE_MAP(theClass, baseClass)                        \
	const DUI_MSGMAP* PASCAL theClass::_GetBaseMessageMap()               \
	{ return &baseClass::messageMap; }                                \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
	{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
	{ &theClass::_GetBaseMessageMap, &theClass::_messageEntries[0] }; \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#else
#define DUI_BEGIN_MESSAGE_MAP(theClass, baseClass)                        \
	const DUI_MSGMAP* theClass::GetMessageMap() const                     \
	{ return &theClass::messageMap; }                                 \
	UILIB_COMDAT const DUI_MSGMAP theClass::messageMap =                  \
	{ &baseClass::messageMap, &theClass::_messageEntries[0] };        \
	UILIB_COMDAT const DUI_MSGMAP_ENTRY theClass::_messageEntries[] =     \
	{                                                                     \

#endif


	//��������
#define DUI_END_MESSAGE_MAP()                                             \
	{ _T(""), _T(""), DuiSig_end, (DUI_PMSG)0 }                           \
	};                                                                        \


	//������Ϣ����--ִ�к�����
#define DUI_ON_MSGTYPE(msgtype, memberFxn)                                \
	{ msgtype, _T(""), DuiSig_vn, (DUI_PMSG)&memberFxn},                  \


	//������Ϣ����--�ؼ�����--ִ�к�����
#define DUI_ON_MSGTYPE_CTRNAME(msgtype,ctrname,memberFxn)                 \
	{ msgtype, ctrname, DuiSig_vn, (DUI_PMSG)&memberFxn },                \


	//����click��Ϣ�Ŀؼ�����--ִ�к�����
#define DUI_ON_CLICK_CTRNAME(ctrname,memberFxn)                           \
	{ DUI_MSGTYPE_CLICK, ctrname, DuiSig_vn, (DUI_PMSG)&memberFxn },      \


	//����selectchanged��Ϣ�Ŀؼ�����--ִ�к�����
#define DUI_ON_SELECTCHANGED_CTRNAME(ctrname,memberFxn)                   \
	{ DUI_MSGTYPE_SELECTCHANGED,ctrname,DuiSig_vn,(DUI_PMSG)&memberFxn }, \


	//����killfocus��Ϣ�Ŀؼ�����--ִ�к�����
#define DUI_ON_KILLFOCUS_CTRNAME(ctrname,memberFxn)                       \
	{ DUI_MSGTYPE_KILLFOCUS,ctrname,DuiSig_vn,(DUI_PMSG)&memberFxn },     \


	//����menu��Ϣ�Ŀؼ�����--ִ�к�����
#define DUI_ON_MENU_CTRNAME(ctrname,memberFxn)                            \
	{ DUI_MSGTYPE_MENU,ctrname,DuiSig_vn,(DUI_PMSG)&memberFxn },          \


	//������ؼ������޹ص���Ϣ��

	//����timer��Ϣ--ִ�к�����
#define DUI_ON_TIMER()                                                    \
	{ DUI_MSGTYPE_TIMER, _T(""), DuiSig_vn,(DUI_PMSG)&OnTimer },          \


	///
	//////////////END��Ϣӳ��궨��////////////////////////////////////////////////////


	//////////////BEGIN�ؼ����ƺ궨��//////////////////////////////////////////////////
	///

#define  DUI_CTR_EDIT                            (_T("Edit"))
#define  DUI_CTR_LIST                            (_T("List"))
#define  DUI_CTR_TEXT                            (_T("Text"))

#define  DUI_CTR_COMBO                           (_T("Combo"))
#define  DUI_CTR_LABEL                           (_T("Label"))
#define  DUI_CTR_FLASH							 (_T("Flash"))

#define  DUI_CTR_BUTTON                          (_T("Button"))
#define  DUI_CTR_OPTION                          (_T("Option"))
#define  DUI_CTR_SLIDER                          (_T("Slider"))

#define  DUI_CTR_CONTROL                         (_T("Control"))
#define  DUI_CTR_ACTIVEX                         (_T("ActiveX"))
#define  DUI_CTR_GIFANIM                         (_T("GifAnim"))

#define  DUI_CTR_LISTITEM                        (_T("ListItem"))
#define  DUI_CTR_PROGRESS                        (_T("Progress"))
#define  DUI_CTR_RICHEDIT                        (_T("RichEdit"))
#define  DUI_CTR_CHECKBOX                        (_T("CheckBox"))
#define  DUI_CTR_COMBOBOX                        (_T("ComboBox"))
#define  DUI_CTR_DATETIME                        (_T("DateTime"))
#define  DUI_CTR_TREEVIEW                        (_T("TreeView"))
#define  DUI_CTR_TREENODE                        (_T("TreeNode"))

#define  DUI_CTR_CONTAINER                       (_T("Container"))
#define  DUI_CTR_TABLAYOUT                       (_T("TabLayout"))
#define  DUI_CTR_SCROLLBAR                       (_T("ScrollBar"))
#define  DUI_CTR_IPADDRESS                       (_T("IPAddress"))

#define  DUI_CTR_LISTHEADER                      (_T("ListHeader"))
#define  DUI_CTR_LISTFOOTER                      (_T("ListFooter"))
#define  DUI_CTR_TILELAYOUT                      (_T("TileLayout"))
#define  DUI_CTR_WEBBROWSER                      (_T("WebBrowser"))

#define  DUI_CTR_CHILDLAYOUT                     (_T("ChildLayout"))
#define  DUI_CTR_LISTELEMENT                     (_T("ListElement"))

#define  DUI_CTR_VERTICALLAYOUT                  (_T("VerticalLayout"))
#define  DUI_CTR_LISTHEADERITEM                  (_T("ListHeaderItem"))

#define  DUI_CTR_LISTTEXTELEMENT                 (_T("ListTextElement"))

#define  DUI_CTR_HORIZONTALLAYOUT                (_T("HorizontalLayout"))
#define  DUI_CTR_LISTLABELELEMENT                (_T("ListLabelElement"))

#define  DUI_CTR_ANIMATIONTABLAYOUT				 (_T("AnimationTabLayout"))

#define  DUI_CTR_LISTCONTAINERELEMENT            (_T("ListContainerElement"))

#define  DUI_CTR_TEXTSCROLL						 (_T("TextScroll"))

#define DUI_CTR_COLORPALETTE					  (_T("ColorPalette"))
	///
	//////////////END�ؼ����ƺ궨��//////////////////////////////////////////////////

	}// namespace DuiLib
