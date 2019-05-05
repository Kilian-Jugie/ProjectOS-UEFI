#ifndef __KOS_HEADER_
#define __KOS_HEADER_

#include <Uefi.h>
#include <Library/UefiApplicationEntryPoint.h>
#include <Library/UefiLib.h>

#include "kTextUtils.h"
#include "kScreen.h"
#include "kUEFI.h"
#include "kTypes.h"

#define kDEBUG



#define WIDE(x) L##x
#define STR(x) #x
#define STR2(x) STR(x)

#define WIDE2(x) L##x
#define WIDE1(x) WIDE2(x)
#define WFILE WIDE1(__FILE__)

#define SUCCESS_MANDATORY(x) if(!success(x)) {fatalError(WFILE, __LINE__, WIDE1(STR(x)), L"Expression was not success.");}

#ifdef kDEBUG
#include <Library/DebugLib.h>
#define D_CHECK_NULLPTR(x) if(!x) {kDebugAssert(__FILE__, __LINE__, "nullptr exception !!!");}
#define D_REQUIRE(x) if(!x){kDebugAssert(__FILE__, __LINE__, STR2(x)" must be initialized before this call !!!");}
#define D_MOD_OS gOS
#define D_MOD_TXTUTILS_IN gOS->textUtils.in
#define D_MOD_TXTUTILS_OUT gOS->textUtils.out
#else
#define D_REQUIRE_KTEXTUTILS_IN
#define D_REQUIRE_KTEXTUTILS_OUT
#define D_CHECK_NULLPTR(x)
#define D_REQUIRE_OS
#endif // DEBUG

#ifdef kDEBUG
#define SUCCESS_MANDATORY_NO_INIT(x) if(!success(x)) {kDebugAssert(__FILE__, __LINE__, "Expression was not success.");}
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
	kUEFI* uefi;
} kOS;

//Initialized in init_kOS
kOS* gOS;
kUEFI* gUEFI;
EFI_SYSTEM_TABLE* gSt;
EFI_BOOT_SERVICES* gBs;


//kOS
EFI_STATUS init_kOS(IN kUEFI* uefi, OUT kOS* out);
VOID kDebugAssert(IN CONST CHAR8* FileName, IN UINTN LineNumber, IN CONST CHAR8* Description);

//General
//Check if a function has successfully being executed
BOOL success(IN EFI_STATUS s);

VOID printSplash();


VOID fatalError(IN EFI_STRING file, IN UINT16 line, IN EFI_STRING cause, IN EFI_STRING description);

VOID waitForKey();

VOID cls();

/*
	Time: time*100ns 

*/
VOID sleep(IN UINT64 time);

VOID kPrintXY(IN UINTN x, IN UINTN y, IN CHAR16* Format, ...);

#endif