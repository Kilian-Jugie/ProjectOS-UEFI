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

/*!
	\brief Basic printf using UEFI features
*/
UINTN kprintf(CONST CHAR16* Format, ...);
/*!
	\brief like printf but to (equivalent) stderr
*/
UINTN keprintf(CONST CHAR16* Format, ...);

/*!
	\brief Entry point
*/
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

//Initialized in InitKOS
//The instance of the OS
kOS* gOS;
kUEFI* gUEFI;
EFI_SYSTEM_TABLE* gSt;
EFI_BOOT_SERVICES* gBs;
//Last error returned by Efi function
//Should be looked when a function returns ST_ERR_UEFI
EFI_STATUS gEfiLastError;


//kOS
/*!
	\brief Initialize all required components for the OS
*/
EFI_STATUS InitKOS(IN kUEFI* uefi, OUT kOS* out);
/*!
	\brief Debug assert which print a message in the edk2 vm
	\param FileName Name of file which throws the error
	\param LineNumber Line which throws the error
	\param Description Description
*/
VOID KDebugAssert(IN CONST CHAR8* FileName, IN UINTN LineNumber, IN CONST CHAR8* Description);

//General
/*!
	\brief Test if a EFI_STATUS OR a kSTATUS is successfull
	Should be moved !
*/
BOOL Success(IN EFI_STATUS s);

/*!
	\brief Print a basic loading screen
*/
VOID PrintSplash();

/*!
	\brief Stop the OS in a fatal status
	\param file File from the error
	\param line Line from the error
	\param cause Line who caused the error
	\param description A message which describe the error
	\param code Optional code from the error
*/
VOID FatalError(IN EFI_STRING file, IN UINT16 line, IN EFI_STRING cause, IN EFI_STRING description, IN UINTN code);

/*!
	\brief Wait a key to be entered
*/
VOID WaitForKey();

/*!
	\brief Clear the screen
*/
VOID cls();

/*
	\brief Tell the os to wait
	\param time Time to wait (/0.1ns)
*/
VOID Sleep(IN UINT64 time);

/*
	\brief Print text at position \a x;\a y with format like printf
*/
VOID KPrintXY(IN UINTN x, IN UINTN y, IN CHAR16* Format, ...);


#endif