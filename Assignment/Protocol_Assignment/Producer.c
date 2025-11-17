#include <Uefi.h>
#include <Library/DebugLib.h>
#include <MyHeader.h>

EFI_GUID gMyMathProtocolGuid = MY_MATH_PROTOCOL_GUID;
EFI_STATUS EFIAPI AddFunc(IN int num1, IN int num2, OUT int *res)
{
    *res = num1 + num2;
    return EFI_SUCCESS;
}
MY_MATH_PROTOCOL mMyMathProtcol = {
    &AddFunc};

EFI_STATUS
EFIAPI
ProducerEntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *gST)
{
    EFI_STATUS Status;
    EFI_BOOT_SERVICES *gBS;
    gBS = gST->BootServices;

    // install protocol
    EFI_HANDLE MathHandle = NULL;
    Status = gBS->InstallProtocolInterface(
        &MathHandle,
        &gMyMathProtocolGuid,
        EFI_NATIVE_INTERFACE,
        (void *)&mMyMathProtcol);

    if (!EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] : Math Protocol INSTALLED \n"));
    }
    else
    {
        DEBUG((DEBUG_ERROR, "[AdiPkg] : Math Protocol NOT INSTALLED | Status : %r \n", Status));
    }
    return EFI_SUCCESS;
}