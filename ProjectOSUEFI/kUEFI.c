/********************************************************************/
 /*! \file: kUEFI.c
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: NONE
 **/
 /*******************************************************************/

#include "kUEFI.h"
#include "kos.h"

VOID InitKUEFI(OUT kUEFI* out, IN EFI_HANDLE handle, IN EFI_SYSTEM_TABLE* st) {
	D_CHECK_NULLPTR(out);
	out->handle = handle;
	out->st = st;
}