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

/*!
	\brief Compare 2 strings
	\param s1 First string
	\param s2 Second string
	\return if differents, index of first difference +1. If equals
	returns 0
*/
UINTN KStrCmp(IN CONST kCHAR* s1, IN CONST kCHAR* s2);

/*!
	\brief String insert
	\param dest String where insert
	\param src String to insert
	\param index Index from the destination where to insert
	\return index + length of src
*/

UINTN KStrIns(OUT kCHAR* dest, IN CONST kCHAR* src, IN UINTN index);

#pragma warning(push)
#pragma warning(disable: 4244)

/*!
	\brief Unsigned int to string
	\param buf Allocated string to store result
	\param base Base of output (10 OR 16)
	\param d Number to convert
*/

VOID KUtoS(kCHAR* buf, UINTN base, UINTN d);
#pragma warning(pop)