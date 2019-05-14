#include "kError.h"
#include "kos.h"


#define KERROR_ADD_FULL(c, d, f) gErrorMap[gErrorMapIndex].code = c; gErrorMap[gErrorMapIndex].desc = d; \
	 gErrorMap[gErrorMapIndex].fatal = f; gErrorMap[gErrorMapIndex].callbacks = NULL; ++gErrorMapIndex 
#define KERROR_ADD(d) KERROR_ADD_FULL(gErrorMapIndex, d, FALSE)


kSTATUS ThrowError(kERRCODE errCode) {
	kERROR* err = GetErrorById(errCode);
	if (!err->callbacks) return ST_OK;
	for (UINTN i = 0; i < err->callbacksIndex; ++i)
		if (err->callbacks[i](err) == FALSE) break;
	return ST_OK;
}

kERROR* GetErrorById(kERRCODE errCode) {
	if (errCode > gErrorMapIndex || gErrorMap[errCode].code != errCode) {
		for (UINTN i = 0; i < gErrorMapIndex; ++i) {
			if (gErrorMap[i].code == errCode)
				return &gErrorMap[i];
		}
		return NULL;
	}
	return &gErrorMap[errCode];
}

kSTATUS InitErrorMap() {
	SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData, KERROR_MAP_SIZE, &gErrorMap)*sizeof(kERROR));
	gErrorMapIndex = 0;

	KERROR_ADD(L"No error");
	KERROR_ADD(L"Unknown error");

	return ST_OK ;
}

kSTATUS _AllocCallback(kERROR* err) {
	D_CHECK_NULLPTR(err);
	if (err->callbacks) return ST_OK;
	err->callbacksIndex = 0;
	SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData, KERROR_MAX_CALLBACK * sizeof(KERROR_CALLBACK_T), (VOID**)&err->callbacks)); //TODO: May not be mandatory !
	return ST_OK;
}

kSTATUS _FreeCallback(kERROR* err) {
	D_CHECK_NULLPTR(err);
	if (!err->callbacks) return ST_OK;
	SUCCESS_MANDATORY(gBs->FreePool(err->callbacks));
	return ST_OK;
}

kSTATUS AddCallback(kERRCODE errCode, KERROR_CALLBACK_T callback) {
	kERROR* err = GetErrorById(errCode);

	if (!err) return ST_ERR_NOT_FOUND;

	if (!err->callbacks) {
		kSTATUS st = _AllocCallback(err);
		if (st != ST_OK) return st;
	}
	else if (err->callbacksIndex == KERROR_MAX_CALLBACK)
		return ST_ERR_ARRAY_FULL;
	err->callbacks[err->callbacksIndex] = callback;
	++err->callbacksIndex;
	return ST_OK;

}

kSTATUS FreeErrorMap() {
	if (!gErrorMap) return ST_OK;

	for (UINTN i = 0; i < gErrorMapIndex; ++i) {
		if (gErrorMap[i].callbacks)
			_FreeCallback(&gErrorMap[i]);
	}

	SUCCESS_MANDATORY(gBs->FreePool(gErrorMap));

	return ST_OK;
}

VOID KPrintError(kERROR* err) {
	kprintf(L"Error: %s Code: %Lu Fatal: %d", err->desc, err->code, err->fatal);
}

BOOL KOSStdCallback(kERROR* err) {
	kprintf(L"[KOS ERRSTDCALLBCK] ");
	KPrintError(err);
	kprintf(L"\n");
	return TRUE;
}

BOOL KOSInternalCallback(kERROR* err) {
	kprintf(L"[KOS ERRINTERNCALLBCK] ");
	KPrintError(err);
	kprintf(L"\n");
	return FALSE;
}