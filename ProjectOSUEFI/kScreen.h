/********************************************************************/
 /** \file: kScreen.h
 *
 * \brief: Screen handling system: output protocol, information getter
 *
 * Source: <kScreen.c>
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
 * 12/05/2019  J.K    NONE    + Prolog
 **/
 /*******************************************************************/

#ifndef __KSCREEN_HEADER_
#define __KSCREEN_HEADER_

#include <Uefi.h>

typedef struct {
	UINT32 height;
	UINT32 width;
	UINT32 colorDepth;
	UINT32 refresh;
} kScreen;

EFI_STATUS init_kScreen(OUT kScreen* out);
VOID kscreen_printInfos(IN kScreen* in);

#endif // !__KSCREEN_HEADER_

