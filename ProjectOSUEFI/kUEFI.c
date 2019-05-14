/********************************************************************/
 /*! \file: kUEFI.c
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

#include "kUEFI.h"
#include "kos.h"

VOID InitKUEFI(kUEFI* out, EFI_HANDLE handle, EFI_SYSTEM_TABLE* st) {
	D_CHECK_NULLPTR(out);
	out->handle = handle;
	out->st = st;
}