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

typedef UINT64 kERRCODE;

typedef kCHAR* kPATH;

typedef BOOLEAN BOOL;

/*typedef UINT64 kSTATUS;

#define KSTATUS_OK 0
#define KSTATUS_OUT_OF_RANGE 1*/

typedef enum {
	ST_OK,
	ST_ERR,
	ST_ERR_ARRAY_FULL,
	ST_ERR_NOT_FOUND
} kSTATUS;

#endif // !__KTYPES_HEADER_
