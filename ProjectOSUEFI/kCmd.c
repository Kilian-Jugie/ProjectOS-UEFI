/********************************************************************/
 /*! \file: kCmd.c
 *
 * \brief: implementation of command line system
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: write loop might use events
 **/
 /*******************************************************************/

#include "kCmd.h"
#include "kos.h"
#include "kString.h"

EFI_STATUS InitKCmd(OUT kCmd* out, IN kPATH defaultPath) {
	D_CHECK_NULLPTR(out);
	D_CHECK_NULLPTR(defaultPath);

	out->history = NULL;
	out->path = defaultPath;

	return EFI_SUCCESS;
}

VOID ReadKeyNolock(IN EFI_KEY_DATA* d) {
	D_REQUIRE(D_MOD_TXTUTILS_IN);
	D_CHECK_NULLPTR(d);
	gOS->textUtils.in->ReadKeyStrokeEx(gOS->textUtils.in, d);
}

VOID ReadKey(IN EFI_KEY_DATA* d) {
	D_REQUIRE(D_MOD_TXTUTILS_IN);
	D_CHECK_NULLPTR(d);
	WaitForKey();
	gOS->textUtils.in->ReadKeyStrokeEx(gOS->textUtils.in, d);
}

EFI_STATUS KCmdLoop(IN kCmd* cmd) {
	D_REQUIRE(D_MOD_TXTUTILS);

	kCHAR* input;
	SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData,  KCMD_MAX_LENGTH*sizeof(kCHAR), (VOID**)&input));
	EFI_KEY_DATA lastIn;
	ReadKeyNolock(&lastIn);

	gOS->textUtils.out->EnableCursor(gOS->textUtils.out, TRUE);
	
	UINTN index = 0;
	BOOL terminate = FALSE;
	while (!terminate) {
		lastIn.Key.ScanCode = SCAN_F1;
		while (lastIn.Key.ScanCode != SCAN_ESC && index < KCMD_MAX_LENGTH) {
			ReadKey(&lastIn);
			if (lastIn.Key.UnicodeChar) {
				kprintf(L"%c", lastIn.Key.UnicodeChar);
				input[index] = lastIn.Key.UnicodeChar;
			}
			++index;
		}
		input[--index] = '\0';
		kprintf(L"\n'%s' VS 'exit'\n", input);
		if (KStrCmp(L"exit", input) == 0)
			terminate = TRUE;
		else {
			kprintf(L"failed %d\n", KStrCmp(L"exit", input));
		}
		index = 0;
	}

	gBs->FreePool(input);


	//if (lastIn.Key.ScanCode == SCAN_ESC)
	//	kprintf(L"ESC !!!");

	/*EFI_KEY_DATA input[KCMD_MAX_LENGTH];
	EFI_KEY_DATA lastIn;

	//for (;;) {
		lastIn.Key.ScanCode = SCAN_F1;
		UINTN i = 0;
		while (lastIn.Key.ScanCode != SCAN_ESC) {
			read_key(&lastIn);
			input[i] = lastIn;
			++i;
			if (lastIn.Key.UnicodeChar)
				kprintf(L"%c", lastIn.Key.UnicodeChar);
		}
		kprintf(L"OK!");
		//break;

	//}*/

	return EFI_SUCCESS;
}