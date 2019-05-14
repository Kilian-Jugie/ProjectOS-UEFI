/********************************************************************/
 /*! \file: kos.c
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: NONE
 *
 * DEVELOPMENT HISTORY:
 *
 * jj/MM/yyyy Author Version Description Of Change
 * ---------- ------ ------- ---------------------
 * 12/05/2019  K.J    NONE   + Prolog
 **/
 /*******************************************************************/

#include "kos.h"
#include "kError.h"
#include <Protocol/HiiFont.h>
#include <Uefi/UefiSpec.h>

UINTN kprintf(CONST CHAR16* Format, ...) {
	return Print(Format);
}

UINTN keprintf(CONST CHAR16* Format, ...) {
	return ErrorPrint(Format);
}

EFI_STATUS EFIAPI KosMain(
	IN EFI_HANDLE        ImageHandle,
	IN EFI_SYSTEM_TABLE* SystemTable) {

	kUEFI uefi;
	InitKUEFI(&uefi, ImageHandle, SystemTable);

	kOS os;
	InitKOS(&uefi, &os);

	return EFI_SUCCESS;
}


EFI_STATUS InitKOS(IN kUEFI* uefi, OUT kOS* out) {
	D_CHECK_NULLPTR(uefi);
	D_CHECK_NULLPTR(out);

	kprintf(L"Initializing KOS...\n");
	
	out->uefi = uefi;

	gOS = out;
	gUEFI = out->uefi;
	gSt = out->uefi->st;
	gBs = out->uefi->st->BootServices;

	SUCCESS_MANDATORY_NO_INIT(InitErrorMap());

	/*
		Needed for SUCCESS_MANDATORY
	*/
	InitKTextUtils(&out->textUtils);
	KTextUtilsPrintInfos(&out->textUtils);

	SUCCESS_MANDATORY(InitKScreen(&out->screen));
	KScreenPrintInfos(&out->screen);

	//kCHAR defPath[] = L"NONE";
	InitKCmd(&out->cmd, L"NONE");
	

	//waitForKey();
	cls();

	AddCallback(1, KOSStdCallback);
	ThrowError(1);

	//PrintSplash();

	//KCmdLoop(&out->cmd);

	/*EFI_HII_FONT_PROTOCOL* hii;
	EFI_STATUS status = uefi->st->BootServices->LocateProtocol(&gEfiHiiFontProtocolGuid, NULL, (VOID * *)& hii);

	if (!success(status)) return status;

	EFI_FONT_DISPLAY_INFO* di;
	hii->GetFontInfo(hii, NULL, NULL, &di, NULL);

	kprintf(L"Using Font %s, size %u, style %u\n", di->FontInfo.FontName, di->FontInfo.FontSize, di->FontInfo.FontStyle);

	uefi->st->BootServices->FreePool(di);

	kprintf(L"azertyuio azertyuio azertyuio azertyuio azertyuio azertyuio azertyuio azertyuio azertyuio azertyuio \n");*/

	//sleep(30000000);

	WaitForKey();

	SUCCESS_MANDATORY(FreeErrorMap());

	WaitForKey();

	return EFI_SUCCESS;
}


BOOL Success(IN EFI_STATUS s) {
	return s == EFI_SUCCESS;
}


VOID WaitForKey() {
	D_REQUIRE(D_MOD_TXTUTILS_IN);
	gBs->WaitForEvent(1, &gOS->textUtils.in->WaitForKeyEx, NULL);
}

VOID FatalError(IN EFI_STRING file, IN UINT16 line, IN EFI_STRING cause, IN EFI_STRING description, IN UINTN code) {
	D_REQUIRE(D_MOD_OS);
	keprintf(L"A fatal error occured during execution. OS must terminate ! File: %s(%u) Description: %s Potential expression causing the error: %s Code: %r", file, line, description, cause, code);
	WaitForKey();
	gSt->RuntimeServices->ResetSystem(EfiResetShutdown, EFI_ABORTED, 0, NULL);
}

VOID cls() {
	D_REQUIRE(D_MOD_TXTUTILS_OUT);
	gOS->textUtils.out->ClearScreen(gOS->textUtils.out);
}

VOID PrintSplash() {
	D_REQUIRE(D_MOD_TXTUTILS_OUT);
	KPrintXY(gOS->textUtils.colNb / 2 - 6, gOS->textUtils.rowNb / 2, L"kOS  v1.0\n");

	for (UINT8 i = 0u; i < 13; ++i) {
		KPrintXY(gOS->textUtils.colNb / 2 + i - 8, gOS->textUtils.rowNb / 2 + 1, L"=");
		Sleep(5000000);
	}
	
	gOS->textUtils.out->SetCursorPosition(gOS->textUtils.out, 1, gOS->textUtils.rowNb - 1);
}

VOID KDebugAssert(IN CONST CHAR8* FileName, IN UINTN LineNumber, IN CONST CHAR8* Description) {
	keprintf(L"[DEBUG ASSERT] File %s\n, Line %Lu\n, Description: %s, Code: %s\n", FileName, LineNumber, Description);
	DebugAssert(FileName, LineNumber, Description);
}

VOID Sleep(UINT64 time) {
	D_REQUIRE(D_MOD_OS);

	EFI_EVENT UserInputDurationTime;
	gBs->CreateEvent(EVT_TIMER, 0, NULL, NULL, &UserInputDurationTime);
	gBs->SetTimer(UserInputDurationTime, TimerRelative, time);
	gBs->WaitForEvent(1, &UserInputDurationTime, NULL);
	gBs->CloseEvent(UserInputDurationTime);
}

VOID KPrintXY(IN UINTN x, IN UINTN y, IN CHAR16* format, ...) {
	D_REQUIRE(D_MOD_TXTUTILS_OUT);
	gOS->textUtils.out->SetCursorPosition(gOS->textUtils.out, x, y);
	gOS->textUtils.out->OutputString(gOS->textUtils.out, format);
}