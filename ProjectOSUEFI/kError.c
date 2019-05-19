#include "kError.h"
#include "kos.h"
#include "kString.h"


#define KERROR_ADD_FULL(c, d, f) gErrorMap[gErrorMapIndex].code = c; gErrorMap[gErrorMapIndex].desc = d; \
	 gErrorMap[gErrorMapIndex].fatal = f; gErrorMap[gErrorMapIndex].callbacks = NULL; ++gErrorMapIndex 
#define KERROR_ADD(d) KERROR_ADD_FULL(gErrorMapIndex, d, FALSE)

kSTATUS _FormatError(IN kERROR* err, OUT kCHAR* out, IN CONST kCHAR* format, ...) {
	const kCHAR* it = err->desc;
	UINTN i = 0;

	//kprintf(err->desc, format);

	VA_LIST args;
	VA_START(args, format);

	while ((*it) != '\0') {
		if ((*it) == '%') {
			++it;
			if ((*it) == '\0') break; //This might be signaled as a warning (using '%' at the end of a string)
			switch (*it) {
			case 'd': {
				INTN buf = VA_ARG(args, INTN);
				kCHAR* strbuf;
				SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData, KERROR_MAX_FORMAT_BUFFER_SIZE * sizeof(kCHAR), &strbuf));
				
				KUtoS(strbuf, 10, buf);
				i = KStrIns(out, strbuf, i);

				SUCCESS_MANDATORY(gBs->FreePool(strbuf));
			}break;
			case 's': {
				kCHAR* buf = VA_ARG(args, kCHAR*);
				i = KStrIns(out, buf, i);
			}
			default:
				out[i] = *it;
				break;
			}
		}
		else
			out[i] = *it;
		++i;
		++it;
	}

	VA_END(args);
	return ST_OK;
}

kSTATUS _ThrowError(kERRCODE errCode, CONST CHAR8* filename, UINTN line, CONST kCHAR* format, ...) {
	kERROR* err = GetErrorById(errCode);
	kCHAR* formated;

	SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData, KERROR_MAX_FORMATED_SIZE * sizeof(kCHAR), &formated));
	_FormatError(err, formated, format);

	if (!err->callbacks) return ST_OK;
	for (UINTN i = 0; i < err->callbacksIndex; ++i)
		if (err->callbacks[i](err, filename, line, format) == FALSE) break;

	SUCCESS_MANDATORY(gBs->FreePool(formated));
	
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
	SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData, KERROR_MAP_SIZE * sizeof(kERROR), &gErrorMap));
	gErrorMapIndex = 0;

	KERROR_ADD(L"No error");
	KERROR_ADD(L"Unknown error: %s");

	return ST_OK ;
}

kSTATUS _AllocErrorCallback(kERROR* err) {
	D_CHECK_NULLPTR(err);
	if (err->callbacks) return ST_OK;
	err->callbacksIndex = 0;
	SUCCESS_MANDATORY(gBs->AllocatePool(EfiBootServicesData, KERROR_MAX_CALLBACK * sizeof(KERROR_CALLBACK_T), (VOID**)&err->callbacks)); //TODO: May not be mandatory !
	return ST_OK;
}

kSTATUS _FreeErrorCallback(kERROR* err) {
	D_CHECK_NULLPTR(err);
	if (!err->callbacks) return ST_OK;
	SUCCESS_MANDATORY(gBs->FreePool(err->callbacks));
	return ST_OK;
}

kSTATUS AddErrorCallback(kERRCODE errCode, KERROR_CALLBACK_T callback) {
	kERROR* err = GetErrorById(errCode);

	if (!err) return ST_ERR_NOT_FOUND;

	if (!err->callbacks) {
		kSTATUS st = _AllocErrorCallback(err);
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
			_FreeErrorCallback(&gErrorMap[i]);
	}

	SUCCESS_MANDATORY(gBs->FreePool(gErrorMap));

	return ST_OK;
}

VOID KPrintError(kERROR* err) {
	kprintf(L"Error: %s Code: %Lu Fatal: %d", err->desc, err->code, err->fatal);
}

BOOL KOSStdCallback(kERROR* err, CONST CHAR8* filename, UINTN line, CONST kCHAR* formated) {
	kprintf(L"[KOS ERRSTDCALLBCK][%s(%Ld)]: ", filename, line);
	KPrintError(err);
	kprintf(L"\n");
	return TRUE;
}

BOOL KOSInternalCallback(kERROR* err, CONST CHAR8* filename, UINTN line, CONST kCHAR* formated) {
	kprintf(L"[KOS ERRINTERNCALLBCK][%s(%Ld)]: ");
	KPrintError(err);
	kprintf(L"\n");
	return FALSE;
}