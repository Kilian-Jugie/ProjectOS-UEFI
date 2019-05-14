/********************************************************************/
 /*! \file: kString.c
 *
 * \brief: implementation string utilities
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: async + SSE2 ?
 *
 * DEVELOPMENT HISTORY:
 *
 * jj/MM/yyyy Author Version Description Of Change
 * ---------- ------ ------- ---------------------
 * 14/05/2019  K.J    NONE   Creation + strcmp
 **/
 /*******************************************************************/
#include "kString.h"


UINTN KStrCmp(IN CONST kCHAR* s1, IN CONST kCHAR* s2) {
	UINTN i = 0;
	while (s1[i] && s2[i]) {
		++i;
		if (s1[i] != s2[i]) return i;
	}
	if ((s1[i] && !s2[i])||(!s1[i]&&s2[i])) return i;
	return 0;
}