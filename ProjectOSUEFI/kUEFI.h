#ifndef __KUEFI_HEADER_
#define __KUEFI_HEADER_

#include <Uefi.h>

typedef struct {
	EFI_HANDLE handle;
	EFI_SYSTEM_TABLE* st;
} kUEFI;

VOID init_kUEFI(kUEFI* out, EFI_HANDLE handle, EFI_SYSTEM_TABLE* st);

#endif // !__KUEFI_HEADER_
