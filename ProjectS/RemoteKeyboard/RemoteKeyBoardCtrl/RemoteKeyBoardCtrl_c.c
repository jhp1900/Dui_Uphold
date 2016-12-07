

/* this ALWAYS GENERATED file contains the RPC client stubs */


 /* File created by MIDL compiler version 8.00.0603 */
/* at Mon Oct 31 15:31:57 2016
 */
/* Compiler settings for RemoteKeyBoardCtrl.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 8.00.0603 
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#if !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_)


#pragma warning( disable: 4049 )  /* more than 64k source lines */
#if _MSC_VER >= 1200
#pragma warning(push)
#endif

#pragma warning( disable: 4211 )  /* redefine extern to static */
#pragma warning( disable: 4232 )  /* dllimport identity*/
#pragma warning( disable: 4024 )  /* array to pointer mapping*/
#pragma warning( disable: 4100 ) /* unreferenced arguments in x86 call */

#pragma optimize("", off ) 

#include <string.h>

#include "RemoteKeyBoardCtrl_h.h"

#define TYPE_FORMAT_STRING_SIZE   43                                
#define PROC_FORMAT_STRING_SIZE   185                               
#define EXPR_FORMAT_STRING_SIZE   1                                 
#define TRANSMIT_AS_TABLE_SIZE    0            
#define WIRE_MARSHAL_TABLE_SIZE   0            

typedef struct _RemoteKeyBoardCtrl_MIDL_TYPE_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ TYPE_FORMAT_STRING_SIZE ];
    } RemoteKeyBoardCtrl_MIDL_TYPE_FORMAT_STRING;

typedef struct _RemoteKeyBoardCtrl_MIDL_PROC_FORMAT_STRING
    {
    short          Pad;
    unsigned char  Format[ PROC_FORMAT_STRING_SIZE ];
    } RemoteKeyBoardCtrl_MIDL_PROC_FORMAT_STRING;

typedef struct _RemoteKeyBoardCtrl_MIDL_EXPR_FORMAT_STRING
    {
    long          Pad;
    unsigned char  Format[ EXPR_FORMAT_STRING_SIZE ];
    } RemoteKeyBoardCtrl_MIDL_EXPR_FORMAT_STRING;


static const RPC_SYNTAX_IDENTIFIER  _RpcTransferSyntax = 
{{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}};


extern const RemoteKeyBoardCtrl_MIDL_TYPE_FORMAT_STRING RemoteKeyBoardCtrl__MIDL_TypeFormatString;
extern const RemoteKeyBoardCtrl_MIDL_PROC_FORMAT_STRING RemoteKeyBoardCtrl__MIDL_ProcFormatString;
extern const RemoteKeyBoardCtrl_MIDL_EXPR_FORMAT_STRING RemoteKeyBoardCtrl__MIDL_ExprFormatString;

#define GENERIC_BINDING_TABLE_SIZE   0            


/* Standard interface: __MIDL_itf_RemoteKeyBoardCtrl_0000_0000, ver. 0.0,
   GUID={0x00000000,0x0000,0x0000,{0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00}} */


/* Standard interface: RemoteKeyBoardCtrl, ver. 1.0,
   GUID={0xB9830DCF,0x103C,0x4A74,{0x8D,0xAA,0xCB,0xC8,0x0E,0x0B,0x77,0x52}} */



static const RPC_CLIENT_INTERFACE RemoteKeyBoardCtrl___RpcClientInterface =
    {
    sizeof(RPC_CLIENT_INTERFACE),
    {{0xB9830DCF,0x103C,0x4A74,{0x8D,0xAA,0xCB,0xC8,0x0E,0x0B,0x77,0x52}},{1,0}},
    {{0x8A885D04,0x1CEB,0x11C9,{0x9F,0xE8,0x08,0x00,0x2B,0x10,0x48,0x60}},{2,0}},
    0,
    0,
    0,
    0,
    0,
    0x00000000
    };
RPC_IF_HANDLE RemoteKeyBoardCtrl_v1_0_c_ifspec = (RPC_IF_HANDLE)& RemoteKeyBoardCtrl___RpcClientInterface;

extern const MIDL_STUB_DESC RemoteKeyBoardCtrl_StubDesc;

static RPC_BINDING_HANDLE RemoteKeyBoardCtrl__MIDL_AutoBindHandle;


unsigned __int64 rkbc_GetStatus( 
    /* [in] */ handle_t IDL_handle)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RemoteKeyBoardCtrl_StubDesc,
                  (PFORMAT_STRING) &RemoteKeyBoardCtrl__MIDL_ProcFormatString.Format[0],
                  ( unsigned char * )&IDL_handle);
    return ( unsigned __int64  )_RetVal.Simple;
    
}


unsigned __int64 rkbc_KeyBoardCtrl( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ int nKey)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RemoteKeyBoardCtrl_StubDesc,
                  (PFORMAT_STRING) &RemoteKeyBoardCtrl__MIDL_ProcFormatString.Format[34],
                  ( unsigned char * )&IDL_handle);
    return ( unsigned __int64  )_RetVal.Simple;
    
}


boolean rkbc_ExecuteExtendCmd( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ ExtendType nType,
    /* [size_is][in] */ const byte *pBuf,
    /* [in] */ long nSize)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RemoteKeyBoardCtrl_StubDesc,
                  (PFORMAT_STRING) &RemoteKeyBoardCtrl__MIDL_ProcFormatString.Format[74],
                  ( unsigned char * )&IDL_handle);
    return ( boolean  )_RetVal.Simple;
    
}


boolean rkbc_GetExtendInfo( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ ExtendType nType,
    /* [in] */ hyper nContext,
    /* [size_is][size_is][out] */ byte **ppBuf,
    /* [out] */ long *pSize)
{

    CLIENT_CALL_RETURN _RetVal;

    _RetVal = NdrClientCall2(
                  ( PMIDL_STUB_DESC  )&RemoteKeyBoardCtrl_StubDesc,
                  (PFORMAT_STRING) &RemoteKeyBoardCtrl__MIDL_ProcFormatString.Format[126],
                  ( unsigned char * )&IDL_handle);
    return ( boolean  )_RetVal.Simple;
    
}


#if !defined(__RPC_WIN32__)
#error  Invalid build platform for this stub.
#endif

#if !(TARGET_IS_NT50_OR_LATER)
#error You need Windows 2000 or later to run this stub because it uses these features:
#error   /robust command line switch.
#error However, your C/C++ compilation flags indicate you intend to run this app on earlier systems.
#error This app will fail with the RPC_X_WRONG_STUB_VERSION error.
#endif


static const RemoteKeyBoardCtrl_MIDL_PROC_FORMAT_STRING RemoteKeyBoardCtrl__MIDL_ProcFormatString =
    {
        0,
        {

	/* Procedure rkbc_GetStatus */

			0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/*  2 */	NdrFcLong( 0x0 ),	/* 0 */
/*  6 */	NdrFcShort( 0x0 ),	/* 0 */
/*  8 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 10 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 12 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 14 */	NdrFcShort( 0x0 ),	/* 0 */
/* 16 */	NdrFcShort( 0x10 ),	/* 16 */
/* 18 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x1,		/* 1 */
/* 20 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 22 */	NdrFcShort( 0x0 ),	/* 0 */
/* 24 */	NdrFcShort( 0x0 ),	/* 0 */
/* 26 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IDL_handle */

/* 28 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 30 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 32 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure rkbc_KeyBoardCtrl */


	/* Return value */

/* 34 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 36 */	NdrFcLong( 0x0 ),	/* 0 */
/* 40 */	NdrFcShort( 0x1 ),	/* 1 */
/* 42 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 44 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 46 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 48 */	NdrFcShort( 0x8 ),	/* 8 */
/* 50 */	NdrFcShort( 0x10 ),	/* 16 */
/* 52 */	0x44,		/* Oi2 Flags:  has return, has ext, */
			0x2,		/* 2 */
/* 54 */	0x8,		/* 8 */
			0x1,		/* Ext Flags:  new corr desc, */
/* 56 */	NdrFcShort( 0x0 ),	/* 0 */
/* 58 */	NdrFcShort( 0x0 ),	/* 0 */
/* 60 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IDL_handle */

/* 62 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 64 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 66 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nKey */

/* 68 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 70 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 72 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Procedure rkbc_ExecuteExtendCmd */


	/* Return value */

/* 74 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 76 */	NdrFcLong( 0x0 ),	/* 0 */
/* 80 */	NdrFcShort( 0x2 ),	/* 2 */
/* 82 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 84 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 86 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 88 */	NdrFcShort( 0x10 ),	/* 16 */
/* 90 */	NdrFcShort( 0x5 ),	/* 5 */
/* 92 */	0x46,		/* Oi2 Flags:  clt must size, has return, has ext, */
			0x4,		/* 4 */
/* 94 */	0x8,		/* 8 */
			0x5,		/* Ext Flags:  new corr desc, srv corr check, */
/* 96 */	NdrFcShort( 0x0 ),	/* 0 */
/* 98 */	NdrFcShort( 0x1 ),	/* 1 */
/* 100 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IDL_handle */

/* 102 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 104 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 106 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter nType */

/* 108 */	NdrFcShort( 0x10b ),	/* Flags:  must size, must free, in, simple ref, */
/* 110 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 112 */	NdrFcShort( 0x6 ),	/* Type Offset=6 */

	/* Parameter pBuf */

/* 114 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 116 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 118 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter nSize */

/* 120 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 122 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 124 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

	/* Procedure rkbc_GetExtendInfo */


	/* Return value */

/* 126 */	0x0,		/* 0 */
			0x48,		/* Old Flags:  */
/* 128 */	NdrFcLong( 0x0 ),	/* 0 */
/* 132 */	NdrFcShort( 0x3 ),	/* 3 */
/* 134 */	NdrFcShort( 0x1c ),	/* x86 Stack size/offset = 28 */
/* 136 */	0x32,		/* FC_BIND_PRIMITIVE */
			0x0,		/* 0 */
/* 138 */	NdrFcShort( 0x0 ),	/* x86 Stack size/offset = 0 */
/* 140 */	NdrFcShort( 0x18 ),	/* 24 */
/* 142 */	NdrFcShort( 0x21 ),	/* 33 */
/* 144 */	0x45,		/* Oi2 Flags:  srv must size, has return, has ext, */
			0x5,		/* 5 */
/* 146 */	0x8,		/* 8 */
			0x3,		/* Ext Flags:  new corr desc, clt corr check, */
/* 148 */	NdrFcShort( 0x1 ),	/* 1 */
/* 150 */	NdrFcShort( 0x0 ),	/* 0 */
/* 152 */	NdrFcShort( 0x0 ),	/* 0 */

	/* Parameter IDL_handle */

/* 154 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 156 */	NdrFcShort( 0x4 ),	/* x86 Stack size/offset = 4 */
/* 158 */	0xe,		/* FC_ENUM32 */
			0x0,		/* 0 */

	/* Parameter nType */

/* 160 */	NdrFcShort( 0x48 ),	/* Flags:  in, base type, */
/* 162 */	NdrFcShort( 0x8 ),	/* x86 Stack size/offset = 8 */
/* 164 */	0xb,		/* FC_HYPER */
			0x0,		/* 0 */

	/* Parameter nContext */

/* 166 */	NdrFcShort( 0x2013 ),	/* Flags:  must size, must free, out, srv alloc size=8 */
/* 168 */	NdrFcShort( 0x10 ),	/* x86 Stack size/offset = 16 */
/* 170 */	NdrFcShort( 0x12 ),	/* Type Offset=18 */

	/* Parameter ppBuf */

/* 172 */	NdrFcShort( 0x2150 ),	/* Flags:  out, base type, simple ref, srv alloc size=8 */
/* 174 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 176 */	0x8,		/* FC_LONG */
			0x0,		/* 0 */

	/* Parameter pSize */

/* 178 */	NdrFcShort( 0x70 ),	/* Flags:  out, return, base type, */
/* 180 */	NdrFcShort( 0x18 ),	/* x86 Stack size/offset = 24 */
/* 182 */	0x3,		/* FC_SMALL */
			0x0,		/* 0 */

			0x0
        }
    };

static const RemoteKeyBoardCtrl_MIDL_TYPE_FORMAT_STRING RemoteKeyBoardCtrl__MIDL_TypeFormatString =
    {
        0,
        {
			NdrFcShort( 0x0 ),	/* 0 */
/*  2 */	
			0x11, 0x0,	/* FC_RP */
/*  4 */	NdrFcShort( 0x2 ),	/* Offset= 2 (6) */
/*  6 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/*  8 */	NdrFcShort( 0x1 ),	/* 1 */
/* 10 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x0,		/*  */
/* 12 */	NdrFcShort( 0xc ),	/* x86 Stack size/offset = 12 */
/* 14 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 16 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 18 */	
			0x11, 0x14,	/* FC_RP [alloced_on_stack] [pointer_deref] */
/* 20 */	NdrFcShort( 0x2 ),	/* Offset= 2 (22) */
/* 22 */	
			0x12, 0x0,	/* FC_UP */
/* 24 */	NdrFcShort( 0x2 ),	/* Offset= 2 (26) */
/* 26 */	
			0x1b,		/* FC_CARRAY */
			0x0,		/* 0 */
/* 28 */	NdrFcShort( 0x1 ),	/* 1 */
/* 30 */	0x28,		/* Corr desc:  parameter, FC_LONG */
			0x54,		/* FC_DEREFERENCE */
/* 32 */	NdrFcShort( 0x14 ),	/* x86 Stack size/offset = 20 */
/* 34 */	NdrFcShort( 0x0 ),	/* Corr flags:  */
/* 36 */	0x1,		/* FC_BYTE */
			0x5b,		/* FC_END */
/* 38 */	
			0x11, 0xc,	/* FC_RP [alloced_on_stack] [simple_pointer] */
/* 40 */	0x8,		/* FC_LONG */
			0x5c,		/* FC_PAD */

			0x0
        }
    };

static const unsigned short RemoteKeyBoardCtrl_FormatStringOffsetTable[] =
    {
    0,
    34,
    74,
    126
    };


static const MIDL_STUB_DESC RemoteKeyBoardCtrl_StubDesc = 
    {
    (void *)& RemoteKeyBoardCtrl___RpcClientInterface,
    MIDL_user_allocate,
    MIDL_user_free,
    &RemoteKeyBoardCtrl__MIDL_AutoBindHandle,
    0,
    0,
    0,
    0,
    RemoteKeyBoardCtrl__MIDL_TypeFormatString.Format,
    1, /* -error bounds_check flag */
    0x50002, /* Ndr library version */
    0,
    0x800025b, /* MIDL Version 8.0.603 */
    0,
    0,
    0,  /* notify & notify_flag routine table */
    0x1, /* MIDL flag */
    0, /* cs routines */
    0,   /* proxy/server info */
    0
    };
#pragma optimize("", on )
#if _MSC_VER >= 1200
#pragma warning(pop)
#endif


#endif /* !defined(_M_IA64) && !defined(_M_AMD64) && !defined(_ARM_) */

