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
 **/
 /*******************************************************************/

#ifndef __KTYPES_HEADER_
#define __KTYPES_HEADER_

#include <Uefi.h>

//Should NEVER EVER BE CHANGED !!! code refactor needed if changed
typedef CHAR16 kCHAR;
typedef INT32 kINT;
typedef INT64 kLONG;

typedef UINT64 kERRCODE;
typedef UINT64 kID;

typedef kCHAR* kPATH;

typedef BOOLEAN BOOL;

/*typedef UINT64 kSTATUS;

#define KSTATUS_OK 0
#define KSTATUS_OUT_OF_RANGE 1*/

/*
	ST_OK MUST BE 0 for compatibility with EFI_STATUS
*/
typedef enum {
	/*
		Success
	*/
	ST_OK,
	/*
		Unknown error (should not be used)
	*/
	ST_ERR,
	/*
		EFI error, check gEfiLastError (kos.h)
	*/
	ST_ERR_UEFI,
	/*
		Array full, in general case, a macro style
		MODULE_MAX_SOMETHING is defined and shows
		the size of array
	*/
	ST_ERR_ARRAY_FULL,
	/*
		Not found in general case, it could be in
		an array
	*/
	ST_ERR_NOT_FOUND
} kSTATUS;

#endif // !__KTYPES_HEADER_
