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

EFI_STATUS init_kCmd(OUT kCmd* out, IN kPATH defaultPath);
EFI_STATUS kCmd_loop(IN kCmd* cmd);
//kSTATUS kCmd_parse(IN CONST kCHAR* cmd);

VOID read_key(IN EFI_KEY_DATA* d);
VOID read_key_nolock(IN EFI_KEY_DATA* d);

#endif // !__KCMD_HEADER_

