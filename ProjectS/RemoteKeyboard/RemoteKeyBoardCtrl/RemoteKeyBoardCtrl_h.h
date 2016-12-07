

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


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

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __RemoteKeyBoardCtrl_h_h__
#define __RemoteKeyBoardCtrl_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifdef __cplusplus
extern "C"{
#endif 


/* interface __MIDL_itf_RemoteKeyBoardCtrl_0000_0000 */
/* [local] */ 

typedef /* [public][public][public][helpstring][uuid][v1_enum] */  DECLSPEC_UUID("23DD4FB4-D3F5-4CC0-A209-3ECB40286C7C") 
enum __MIDL___MIDL_itf_RemoteKeyBoardCtrl_0000_0000_0001
    {
        kExtendType_Unknown	= 0,
        kExtendType_LessionInfo	= ( kExtendType_Unknown + 1 ) 
    } 	ExtendType;



extern RPC_IF_HANDLE __MIDL_itf_RemoteKeyBoardCtrl_0000_0000_v0_0_c_ifspec;
extern RPC_IF_HANDLE __MIDL_itf_RemoteKeyBoardCtrl_0000_0000_v0_0_s_ifspec;

#ifndef __RemoteKeyBoardCtrl_INTERFACE_DEFINED__
#define __RemoteKeyBoardCtrl_INTERFACE_DEFINED__

/* interface RemoteKeyBoardCtrl */
/* [version][uuid] */ 

unsigned __int64 rkbc_GetStatus( 
    /* [in] */ handle_t IDL_handle);

unsigned __int64 rkbc_KeyBoardCtrl( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ int nKey);

boolean rkbc_ExecuteExtendCmd( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ ExtendType nType,
    /* [size_is][in] */ const byte *pBuf,
    /* [in] */ long nSize);

boolean rkbc_GetExtendInfo( 
    /* [in] */ handle_t IDL_handle,
    /* [in] */ ExtendType nType,
    /* [in] */ hyper nContext,
    /* [size_is][size_is][out] */ byte **ppBuf,
    /* [out] */ long *pSize);



extern RPC_IF_HANDLE RemoteKeyBoardCtrl_v1_0_c_ifspec;
extern RPC_IF_HANDLE RemoteKeyBoardCtrl_v1_0_s_ifspec;
#endif /* __RemoteKeyBoardCtrl_INTERFACE_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


