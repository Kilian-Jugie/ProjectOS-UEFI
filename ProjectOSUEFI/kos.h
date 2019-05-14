/********************************************************************/
 /** \file: kos.h
 *
 * \brief: Main file for kOS
 *
 * Source: <kos.c>
 * EXTERNAL VARIABLES:
 *
 * Name Description
 * ---- -----------
 * NONE NONE
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: EDK2
 *
 * NOTES: NONE
 *
 * DEVELOPMENT HISTORY:
 *
 * jj/MM/yyyy Author Version Description Of Change
 * ---------- ------ ------- ---------------------
 * 12/05/2019  J.K    NONE    + Prolog
 **/
 /*******************************************************************/

#ifndef __KOS_HEADER_
#define __KOS_HEADER_

#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>

#include "kTextUtils.h"
#include "kScreen.h"
#include "kUEFI.h"
#include "kTypes.h"
#include "kCmd.h"

#define kDEBUG

#define WIDE(x) L##x
#define STR(x) #x
#define STR2(x) STR(x)

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define WFILE WIDE1(__FILE__)

#define SUCCESS_MANDATORY(x) { EFI_STATUS __sm_st = x; if(!Success(__sm_st)) {FatalError(WFILE, __LINE__, WIDE1(STR(x)), L"Expression was not success.", __sm_st);} }

#ifdef kDEBUG
#include <Library/DebugLib.h>
#define D_CHECK_NULLPTR(x) if(!x) {KDebugAssert(__FILE__, __LINE__, "nullptr exception !!!");}
#define D_REQUIRE(x) if(!x){KDebugAssert(__FILE__, __LINE__, STR2(x)" must be initialized before this call !!!");}
#define D_MOD_OS gOS
#define D_MOD_TXTUTILS_IN gOS->textUtils.in
#define D_MOD_TXTUTILS_OUT gOS->textUtils.out
#define D_MOD_TXTUTILS (D_MOD_TXTUTILS_IN && D_MOD_TXTUTILS_OUT)
#else
#define D_MOD_KTEXTUTILS_IN
#define D_MOD_KTEXTUTILS_OUT
#define D_MOD_KTEXTUTILS
#define D_MOD_OS
#define D_CHECK_NULLPTR(x)
#define D_REQUIRE(x)
#endif // DEBUG

#ifndef K_COMPILER_NO_ASSUME
#define ASSUME(x) __assume(x)
#else
#define ASSUME(x) 
#endif // !K_COMPILER_NO_ASSUME


#ifdef kDEBUG
#define SUCCESS_MANDATORY_NO_INIT(x) if(!Success(x)) {KDebugAssert(__FILE__, __LINE__, "Expression was not success.");}
#else
//A definir
#define SUCCESS_MANDATORY_NO_INIT(x) x
#endif

UINTN kprintf(CONST CHAR16* Format, ...);
UINTN keprintf(CONST CHAR16* Format, ...);

EFI_STATUS
EFIAPI
KosMain(
	IN EFI_HANDLE        ImageHandle,
	IN EFI_SYSTEM_TABLE* SystemTable
);

typedef struct {
	kTextUtils textUtils;
	kScreen screen;
	kCmd cmd;
	kUEFI* uefi;
} kOS;

//Initialized in init_kOS
kOS* gOS;
kUEFI* gUEFI;
EFI_SYSTEM_TABLE* gSt;
EFI_BOOT_SERVICES* gBs;


//kOS
EFI_STATUS InitKOS(IN kUEFI* uefi, OUT kOS* out);
VOID KDebugAssert(IN CONST CHAR8* FileName, IN UINTN LineNumber, IN CONST CHAR8* Description);

//General
//Check if a function has successfully being executed
BOOL Success(IN EFI_STATUS s);

VOID PrintSplash();


VOID FatalError(IN EFI_STRING file, IN UINT16 line, IN EFI_STRING cause, IN EFI_STRING description, IN UINTN code);

VOID WaitForKey();

VOID cls();

/*
	time: /0.1ns 

*/
VOID Sleep(IN UINT64 time);

VOID KPrintXY(IN UINTN x, IN UINTN y, IN CHAR16* Format, ...);


#endif