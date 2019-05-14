#ifndef __KERROR_HEADER_
#define __KERROR_HEADER_

#include "kTypes.h"

/*
	TODO: ++mapsize || dyn (realloc)
	TODO: ++maxcall || "	"
*/

#define KERROR_MAP_SIZE 8192
#define KERROR_MAX_CALLBACK 32

typedef struct kERROR kERROR;

/*
	\return return FALSE to stop callbacks calling
*/
typedef BOOL(*KERROR_CALLBACK_T)(IN kERROR*);

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

kSTATUS AddCallback(kERRCODE errCode, KERROR_CALLBACK_T callback);

kSTATUS ThrowError(kERRCODE errCode);
kERROR* GetErrorById(kERRCODE errCode);

kSTATUS _AllocCallback(kERROR* err);
kSTATUS _FreeCallback(kERROR* err);

VOID KPrintError(kERROR* err);

BOOL KOSStdCallback(kERROR* err);
BOOL KOSInternalCallback(kERROR* err);

kERROR* gErrorMap;
static UINTN gErrorMapIndex;

#endif // !__KERROR_HEADER_
