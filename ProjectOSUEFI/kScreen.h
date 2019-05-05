#ifndef __KSCREEN_HEADER_
#define __KSCREEN_HEADER_

#include <Uefi.h>

typedef struct {
	UINT32 height;
	UINT32 width;
	UINT32 colorDepth;
	UINT32 refresh;
} kScreen;

EFI_STATUS init_kScreen(OUT kScreen* out);
VOID kscreen_printInfos(IN kScreen* in);

#endif // !__KSCREEN_HEADER_

