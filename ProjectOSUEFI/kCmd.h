/********************************************************************/
 /** \file: kCmd.h
 *
 * \brief: Command line system for kOS
 *
 * Source: <kCmd.c>
 * EXTERNAL VARIABLES:
 *
 * Name Description
 * ---- -----------
 * NONE NONE
 *
 * ASSUMPTIONS, CONSTRAINTS, RESTRICTIONS: NONE
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

#ifndef __KCMD_HEADER_
#define __KCMD_HEADER_
#include "kTypes.h"

#define KCMD_MAX_LENGTH 8192

typedef struct kCmdEntry kCmdEntry;

struct kCmdEntry {
	kCHAR* entry;
	kCmdEntry* next;
};

typedef struct {
	kCmdEntry* history;
	kPATH path;
} kCmd;

EFI_STATUS InitKCmd(OUT kCmd* out, IN kPATH defaultPath);
/*!
	\brief Wait user input and process it
*/
EFI_STATUS KCmdLoop(IN kCmd* cmd);

/*!
	\brief Parse an input
*/
kSTATUS KCmdParse(IN CONST kCHAR* cmd);

/*!
	\brief Wait for a key and get it
	Should be moved !
*/
VOID ReadKey(IN EFI_KEY_DATA* d);

/*!
	\brief Get a key change without locking state
	Should be moved !
*/
VOID ReadKeyNolock(IN EFI_KEY_DATA* d);

#endif // !__KCMD_HEADER_

