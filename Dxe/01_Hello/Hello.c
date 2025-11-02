#include <Uefi.h>
#include <Library/DebugLib.h>

EFI_STATUS EFIAPI EntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] :Hello DXE Driver===========\r\n"));

    return EFI_SUCCESS;
}
