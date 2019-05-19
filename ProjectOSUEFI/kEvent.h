/********************************************************************/
 /** \file: kEvent.h
 *
 * \brief: Event system and handling
 *
 * Source: <kEvent.c>
 * EXTERNAL VARIABLES:
 *
 * Name Description
 * ---- -----------
 * NONE NONE
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
 *
 * NOTES: Async
 **/
 /*******************************************************************/

#ifndef __KEVENTDISPATCHER_H_
#define __KEVENTDISPATCHER_H_
#include "kTypes.h"

#define KEVENT_MAX_ID 4096
#define KEVENT_MAX_CALLBACKS 32

typedef BOOL(*KEVENT_CALLBACK_T)(VOID*);

typedef struct {
	kID id;
	KEVENT_CALLBACK_T* callbacks;
	UINTN callbackNb;
} kEvent;

typedef enum {
	KEID_OTHER
} kEventIds;

kEvent* gEvents;
UINTN gEventIndex;

kSTATUS InitEventSystem();
kSTATUS FreeEventSystem();


/*!
	\brief Create a new event and push it to the event list
	\param returnStatus 
	\return The ID of the event
*/
UINTN CreateEvent(OUT OPTIONAL kSTATUS* returnStatus);

/*!
	\brief Free allocated memory by an event
	\param event Event to free
*/
kSTATUS FreeEvent(IN kEvent* event);

/*!
	\brief see @FreeEvent
	\param id Id of the event to free
*/
kSTATUS FreeEventId(UINTN id);

/*!
	\brief Get a pointer to an event from and id
	\param id The id of the event to get
	\return The pointer to the event. If id not
	correct, return NULL
*/
kEvent* GetEvent(UINTN id);

/*!
	\brief Add a callback function which will be called
	when the event will be throwed
	\param event Event to add the callback
	\param c Function to call when event is throwed
*/
kSTATUS AddCallbackToEvent(IN kEvent* event, KEVENT_CALLBACK_T c);

/*!
	\brief Call all callbacks of an event (see @AddCallbackToEvent)
	\param event Event to call callbacks
	\param data A pointer to an eventual data to pass to the
	callback function. This can be NULL but ressource managment
	must be done by user
*/
VOID ThrowEvent(IN kEvent* event, IN VOID* data);

/*!
	\brief See @ThrowEvent
	\param id Id of the event to call callbacks
	\param data See @ThrowEvent
*/
VOID ThrowEventId(IN UINTN id, IN VOID* data);

#endif // !__KEVENTDISPATCHER_H_

