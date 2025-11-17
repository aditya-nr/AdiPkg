#ifndef __MY_HEADER_H
#define __MY_HEADER_H

#include <Uefi.h>

#define MY_MATH_PROTOCOL_GUID \
    {0X7A0D7317, 0XB19A, 0X4DBB, {0XBD, 0X66, 0X73, 0X68, 0X85, 0X16, 0X74, 0XE8}}

extern EFI_GUID gMyMathProtocolGuid;

typedef EFI_STATUS(EFIAPI *ADD_FUNC)(int num1, int num2, int *res);

typedef struct
{
    ADD_FUNC Add;
} MY_MATH_PROTOCOL;

#endif