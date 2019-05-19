/********************************************************************/
 /*! \file: kEvent.c
 *
 * \brief: implementation event system
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: async ?
 **/
 /*******************************************************************/

#include "kEvent.h"
#include "kos.h"

kSTATUS InitEventSystem() {
	EFI_STATUS st = gBs->AllocatePool(EfiBootServicesData, KEVENT_MAX_ID * sizeof(kEvent), &gEvents);
	if (!Success(st)) {
		gEfiLastError = st;
		return ST_ERR_UEFI;
	}
	return ST_OK;
}

kSTATUS FreeEventSystem() {
	kSTATUS st = gBs->FreePool(gEvents);
	if (!Success(st)) {
		gEfiLastError = st;
		return ST_ERR_UEFI;
	}
	return ST_OK;
}

UINTN CreateEvent(OUT OPTIONAL kSTATUS* returnStatus) {
	gEvents[gEventIndex].id = gEventIndex;
	gEvents[gEventIndex].callbackNb = 0;
	EFI_STATUS st = gBs->AllocatePool(EfiBootServicesData, KEVENT_MAX_CALLBACKS * sizeof(KEVENT_CALLBACK_T), (VOID**)&gEvents[gEventIndex].callbacks);
	if (!Success(st)) {
		if (returnStatus)* returnStatus = ST_ERR_UEFI;
		gEfiLastError = st;
		return 0;
	}
	++gEventIndex;
	if (returnStatus)* returnStatus = ST_OK;
	return gEventIndex-1;
}

kSTATUS FreeEvent(IN kEvent* event) {
	if (!event->callbacks) return ST_OK;
	kSTATUS st = gBs->FreePool(event->callbacks);
	if (!Success(st)) {
		gEfiLastError = st;
		return ST_ERR_UEFI;
	}
	return ST_OK;
}

kSTATUS FreeEventId(UINTN id) {
	return FreeEvent(GetEvent(id));
}

kEvent* GetEvent(UINTN id) {
	if (id >= gEventIndex) return NULL;
	return &gEvents[id];
}

VOID ThrowEventId(IN UINTN id, IN VOID* data) {
	ThrowEvent(GetEvent(id), data);
}

VOID ThrowEvent(IN kEvent* event, IN VOID* data) {
	BOOL r = TRUE;
	for (UINTN i = 0; i < event->callbackNb; ++i) {
		r = event->callbacks[i](data);
		if (r != TRUE) break;
	}
}

kSTATUS AddCallbackToEvent(IN kEvent* event, KEVENT_CALLBACK_T c) {
	if (event->callbackNb == KEVENT_MAX_CALLBACKS)
		return ST_ERR_ARRAY_FULL;
	event->callbacks[event->callbackNb] = c;
	++event->callbackNb;
	return ST_OK;
}