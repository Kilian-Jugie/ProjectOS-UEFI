#ifndef __KCMD_HEADER_
#define __KCMD_HEADER_
#include "kTypes.h"

struct kCmdEntry {
	kCHAR* entry;
	kCmdEntry* next;
};

struct kCmd {
	kCmdEntry* history;


};


#endif // !__KCMD_HEADER_

