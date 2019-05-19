/********************************************************************/
 /** \file: kUEFI.h
 *
 * \brief: Wrapper for UEFI
 *
 * Source: <kUEFI.c>
 * EXTERNAL VARIABLES:
 *
 * Name Description
 * ---- -----------
 * NONE NONE
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: NONE
 **/
 /*******************************************************************/

#ifndef __KUEFI_HEADER_
#define __KUEFI_HEADER_

#include <Uefi.h>

typedef struct {
	EFI_HANDLE handle;
	EFI_SYSTEM_TABLE* st;
} kUEFI;

VOID InitKUEFI(OUT kUEFI* out, IN EFI_HANDLE handle, IN EFI_SYSTEM_TABLE* st);

#endif // !__KUEFI_HEADER_
