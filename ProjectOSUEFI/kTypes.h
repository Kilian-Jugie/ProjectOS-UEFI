/********************************************************************/
 /** \file: kTypes.h
 *
 * \brief: kOS custom types
 *
 * Source: NO SOURCE
 * EXTERNAL VARIABLES:
 *
 * Name Description
 * ---- -----------
 * NONE NONE
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: BOOL not defined !!!
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

#ifndef __KTYPES_HEADER_
#define __KTYPES_HEADER_

#include <Uefi.h>

typedef CHAR16 kCHAR;
typedef INT32 kINT;
typedef INT64 kLONG;
typedef double kFLOAT;

typedef kCHAR* kPATH;

typedef BOOLEAN BOOL;

typedef INT64 kSTATUS;

#endif // !__KTYPES_HEADER_
