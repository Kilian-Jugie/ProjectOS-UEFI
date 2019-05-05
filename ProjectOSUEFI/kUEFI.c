#include "kUEFI.h"
#include "kos.h"

VOID init_kUEFI(kUEFI* out, EFI_HANDLE handle, EFI_SYSTEM_TABLE* st) {
	D_CHECK_NULLPTR(out);
	out->handle = handle;
	out->st = st;
}