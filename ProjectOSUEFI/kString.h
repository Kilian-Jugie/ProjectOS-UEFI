/********************************************************************/
 /** \file: kString.h
 *
 * \brief: string utilities
 *
 * Source: <kString.c>
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

#include "kTypes.h"

UINTN KStrCmp(IN CONST kCHAR* s1, IN CONST kCHAR* s2);

UINTN KStrIns(OUT kCHAR* dest, IN CONST kCHAR* src, IN UINTN index);

/*
   Only base 10 & 16 !
*/

#pragma warning(push)
#pragma warning(disable: 4244)
VOID KUtoS(kCHAR* buf, UINTN base, UINTN d);
#pragma warning(pop)