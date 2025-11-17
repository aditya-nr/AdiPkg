#include <Uefi.h>
#include <Library/DebugLib.h>
#include <MyHeader.h>

EFI_GUID gMyMathProtocolGuid = MY_MATH_PROTOCOL_GUID;

EFI_STATUS
EFIAPI
ConsumerEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *gST)
{
    EFI_STATUS Status;
    EFI_BOOT_SERVICES *gBS;
    gBS = gST->BootServices;

    // install protocol
    MY_MATH_PROTOCOL *mMyMathProtcol;
    Status = gBS->LocateProtocol(&gMyMathProtocolGuid, NULL, (void **)&mMyMathProtcol);

    if (!EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] : Loaded Math Protocol\n"));
        int res;
        Status = mMyMathProtcol->Add(5, 6, &res);
        DEBUG((DEBUG_INFO, "[AdiPkg] : Called Add Func \n Result : 5+6=%u\n", res));
    }
    return EFI_SUCCESS;
}