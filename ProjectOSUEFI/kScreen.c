/********************************************************************/
 /*! \file: kScreen.c
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: NONE
 *
 * DEVELOPMENT HISTORY:
 **/
 /*******************************************************************/

#include "kScreen.h"
#include "kos.h"

#include <Protocol/UgaDraw.h>

EFI_STATUS InitKScreen(OUT kScreen* out) {
	D_CHECK_NULLPTR(out);
	D_REQUIRE(D_MOD_OS);

	EFI_UGA_DRAW_PROTOCOL* uga;
	EFI_STATUS status;
	SUCCESS_MANDATORY(gSt->BootServices->LocateProtocol(&gEfiUgaDrawProtocolGuid, NULL, (VOID * *)& uga));

	status = uga->GetMode(uga, &out->height, &out->width, &out->colorDepth, &out->refresh);

	return status;
}

VOID KScreenPrintInfos(IN kScreen* in) {
	D_CHECK_NULLPTR(in);
	kprintf(L"Screen stats: %ux%u (%ubits, %uHz)\n", in->height, in->width, in->colorDepth, in->refresh);
}
