#ifndef __KTEXTUTILS_HEADER_
#define __KTEXTUTILS_HEADER_

#include <Protocol/SimpleTextOut.h>
#include <Protocol/SimpleTextInEx.h>
#include <Uefi.h>

typedef struct {
	EFI_SIMPLE_TEXT_OUTPUT_PROTOCOL* out;
	EFI_SIMPLE_TEXT_INPUT_EX_PROTOCOL* in;
	UINTN colNb, rowNb;
} kTextUtils;

EFI_STATUS init_kTextUtils(OUT kTextUtils* out);
VOID kTextUtils_printInfos(IN kTextUtils* in);

#endif