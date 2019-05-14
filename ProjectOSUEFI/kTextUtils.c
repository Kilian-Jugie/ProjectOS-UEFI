/********************************************************************/
 /*! \file: kTextUtils.c
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

#include "kTextUtils.h"
#include "kos.h"

VOID kTextUtils_printInfos(IN kTextUtils* in) {
	D_CHECK_NULLPTR(in);
	kprintf(L"Text stats: %u columns, %u rows\n", in->colNb, in->rowNb);
}

EFI_STATUS init_kTextUtils(OUT kTextUtils* out) {
	D_CHECK_NULLPTR(out);
	D_REQUIRE(D_MOD_OS);

	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* sti;
	SUCCESS_MANDATORY_NO_INIT(gBs->LocateProtocol(&gEfiSimpleTextInputExProtocolGuid, NULL, (VOID * *)& sti));
	out->in = sti;

	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* sto;
	SUCCESS_MANDATORY(gBs->LocateProtocol(&gEfiSimpleTextOutProtocolGuid, NULL, (VOID * *)& sto));
	out->out = sto;

	out->out->QueryMode(out->out, 0, &out->colNb, &out->rowNb);

	return EFI_SUCCESS;
}



