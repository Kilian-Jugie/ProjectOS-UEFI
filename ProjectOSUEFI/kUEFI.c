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

VOID InitKUEFI(kUEFI* out, EFI_HANDLE handle, EFI_SYSTEM_TABLE* st) {
	D_CHECK_NULLPTR(out);
	out->handle = handle;
	out->st = st;
}