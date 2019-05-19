/********************************************************************/
 /** \file: kError.h
 *
 * \brief: Error event standard system
 *
 * Source: <kError.c>
 * EXTERNAL VARIABLES:
 *
 * Name Description
 * ---- -----------
 * NONE NONE
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: To pass with kEvent !
 **/
 /*******************************************************************/

#ifndef __KERROR_HEADER_
#define __KERROR_HEADER_

#include "kTypes.h"

/*
	TODO: ++mapsize || dyn (realloc)
	TODO: ++maxcall || "	"
*/

#define KERROR_MAP_SIZE 8192
#define KERROR_MAX_CALLBACK 32
#define KERROR_MAX_FORMATED_SIZE 4096
#define KERROR_MAX_FORMAT_BUFFER_SIZE KERROR_MAX_FORMATED_SIZE

typedef struct kERROR kERROR;

/*
	\return return FALSE to stop callbacks calling
*/
typedef BOOL(*KERROR_CALLBACK_T)(IN kERROR*, CONST CHAR8*, UINTN, CONST kCHAR*);

#pragma pack(push)
#pragma pack(1) //Sinon desc est ignoré (à monter voir calcul)
struct kERROR {
	kERRCODE code;
	CONST kCHAR* desc;
	BOOL fatal;
	KERROR_CALLBACK_T* callbacks;
	UINTN callbacksIndex;
};
#pragma pack(pop)

kSTATUS InitErrorMap();
kSTATUS FreeErrorMap();

kSTATUS AddErrorCallback(kERRCODE errCode, KERROR_CALLBACK_T callback);

#define ThrowError(err, ...) _ThrowError(err, __FILE__, __LINE__, __VA_ARGS__)
kSTATUS _ThrowError(kERRCODE errCode, CONST CHAR8* filename, UINTN line, CONST kCHAR* format, ...);
kERROR* GetErrorById(kERRCODE errCode);

kSTATUS _FormatError(IN kERROR* err, OUT kCHAR* out, IN CONST kCHAR* format, ...);

kSTATUS _AllocErrorCallback(kERROR* err);
kSTATUS _FreeErrorCallback(kERROR* err);

VOID KPrintError(kERROR* err);

BOOL KOSStdCallback(kERROR* err, CONST CHAR8* filename, UINTN line, CONST kCHAR* formated);
BOOL KOSInternalCallback(kERROR* err, CONST CHAR8* filename, UINTN line, CONST kCHAR* formated);

kERROR* gErrorMap;
static UINTN gErrorMapIndex;

#endif // !__KERROR_HEADER_
