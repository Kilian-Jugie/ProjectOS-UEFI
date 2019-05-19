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

UINTN KStrIns(OUT kCHAR* dest, IN CONST kCHAR* src, IN UINTN index) {
	UINTN i = 0;
	while (dest[index] && src[i]) {
		dest[index] = src[i];
		++i; ++index;
	}
	return index;
}

UINTN KStrInsEx(OUT kCHAR* dest, IN CONST kCHAR* src, IN UINTN index, IN UINTN size) {
	UINTN i = 0;
	while (--size >= 0) {
		dest[index++] = src[i++];
	}
	return index;
}

#pragma warning(push)
#pragma warning(disable: 4244)

VOID KUtoS(kCHAR* buf, UINTN base, UINTN d) {
	kCHAR* p = buf;
	kCHAR* p1, * p2;
	UINTN ud = d;
	INTN divisor = 10;

	if (base == 16)
		divisor = 16;

	do {
		INTN remainder = ud % divisor;

		*p++ = (remainder < (INTN)10) ? remainder + L'0' : remainder + L'A' - (INTN)10;
	} while (ud /= divisor);

	*p = 0;

	p1 = buf;
	p2 = p - 1;
	while (p1 < p2) {
		kCHAR tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2--;
	}
	*p1 = '\0';
}
#pragma warning(pop)