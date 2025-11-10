#ifndef __HEADER_H
#define __HEADER_H

#include <Uefi.h>

#define MY_DEVICE_PROTO_GUID \
    {0X8A64E182, 0XB370, 0X45AE, {0XBE, 0XC2, 0X12, 0X81, 0XD2, 0XAB, 0XCD, 0X13}}

#define MY_DEVICE_PATH_GUID \
    {0X86A0564C, 0X55BB, 0X4E7E, {0XA5, 0X99, 0X24, 0X8A, 0X60, 0X3E, 0XD6, 0X72}}

typedef struct
{
    VENDOR_DEVICE_PATH Vendor;
    EFI_DEVICE_PATH End;
} MY_DEVICE_PATH;

extern EFI_GUID gMyDeviceProtocolGuid;
// extern EFI_GUID gMyDevicePathGuid;

// Define a simple protocol structure
typedef struct
{
    UINTN DeviceId;
} MY_DEVICE_PROTOCOL;

#endif