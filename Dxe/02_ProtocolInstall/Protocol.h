#ifndef __PROTOCOL_H
#define __PROTOCOL_H

#include <Uefi.h>

#define PRINT_HELLO_PROTO_GUID \
    {0xc738daf9, 0x9d05, 0x4e44, {0x8d, 0x03, 0x0e, 0xb8, 0x7d, 0x7d, 0xd3, 0xa9}}

typedef EFI_STATUS(EFIAPI *PRINT_HELLO)(
    void);

typedef struct
{
    PRINT_HELLO Print;
} _PRINT_HELLO_PROTOCOL;

typedef _PRINT_HELLO_PROTOCOL PRINT_HELLO_PROTOCOL;

extern EFI_GUID gPrintHelloProtoGuid;
#endif