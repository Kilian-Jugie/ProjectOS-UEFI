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
 *
 * DEVELOPMENT HISTORY:
 *
 * jj/MM/yyyy Author Version Description Of Change
 * ---------- ------ ------- ---------------------
 * 14/05/2019  J.K    NONE    Creation + strcmp
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