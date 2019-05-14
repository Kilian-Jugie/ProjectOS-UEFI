/********************************************************************/
 /*! \file: kCmd.c
 *
 * \brief: implementation of command line system
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: write loop might use events
 *
 * DEVELOPMENT HISTORY:
 *
 * jj/MM/yyyy Author Version Description Of Change
 * ---------- ------ ------- ---------------------
 * 12/05/2019  K.J    NONE   + Prolog + kCmdloop
 **/
 /*******************************************************************/

#include "kCmd.h"
#include "kos.h"
#include "kString.h"

EFI_STATUS init_kCmd(OUT kCmd* out, IN kPATH defaultPath) {
	D_CHECK_NULLPTR(out);
	D_CHECK_NULLPTR(defaultPath);

	out->history = NULL;
	out->path = defaultPath;

	return EFI_SUCCESS;
}

VOID read_key_nolock(IN EFI_KEY_DATA* d) {
	D_REQUIRE(D_MOD_TXTUTILS_IN);
	D_CHECK_NULLPTR(d);
	gOS->textUtils.in->ReadKeyStrokeEx(gOS->textUtils.in, d);
}

VOID read_key(IN EFI_KEY_DATA* d) {
	D_REQUIRE(D_MOD_TXTUTILS_IN);
	D_CHECK_NULLPTR(d);
	waitForKey();
	gOS->textUtils.in->ReadKeyStrokeEx(gOS->textUtils.in, d);
}

EFI_STATUS kCmd_loop(IN kCmd* cmd) {
	D_REQUIRE(D_MOD_TXTUTILS);

	kCHAR* input;
	SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData,  KCMD_MAX_LENGTH*sizeof(kCHAR), (VOID**)&input));
	EFI_KEY_DATA lastIn;
	read_key_nolock(&lastIn);

	gOS->textUtils.out->EnableCursor(gOS->textUtils.out, TRUE);
	
	UINTN index = 0;
	BOOL terminate = FALSE;
	while (!terminate) {
		lastIn.Key.ScanCode = SCAN_F1;
		while (lastIn.Key.ScanCode != SCAN_ESC && index < KCMD_MAX_LENGTH) {
			read_key(&lastIn);
			if (lastIn.Key.UnicodeChar) {
				kprintf(L"%c", lastIn.Key.UnicodeChar);
				input[index] = lastIn.Key.UnicodeChar;
			}
			++index;
		}
		input[--index] = '\0';
		kprintf(L"\n'%s' VS 'exit'\n", input);
		if (kstrcmp(L"exit", input) == 0)
			terminate = TRUE;
		else {
			kprintf(L"failed %d\n", kstrcmp(L"exit", input));
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