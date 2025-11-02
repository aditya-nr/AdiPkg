#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Protocol.h>

EFI_GUID gPrintHelloProtoGuid = PRINT_HELLO_PROTO_GUID;

EFI_STATUS EFIAPI PrintHello(void)
{
    DEBUG((DEBUG_INFO, "Print : Hello World !\n"));
    return EFI_SUCCESS;
}

PRINT_HELLO_PROTOCOL mProtocol = {
    &PrintHello};

EFI_STATUS
EFIAPI
EntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *gST)
{
    DEBUG((DEBUG_INFO, "=============START : 02_Protocol_Install : Entry Point====================\n"));
    EFI_HANDLE handle = NULL;
    EFI_BOOT_SERVICES *gBS = gST->BootServices;

    EFI_STATUS status = gBS->InstallProtocolInterface(
        &handle,
        &gPrintHelloProtoGuid,
        EFI_NATIVE_INTERFACE,
        &mProtocol);

    if (!EFI_ERROR(status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] : Protocol Installed\n"));
        DEBUG((DEBUG_INFO, "[AdiPkg] : EFI_HANDLE value  = %p\n", handle));
        DEBUG((DEBUG_INFO, "[AdiPkg] : INTERFACE address = %p\n", &mProtocol));
    }
    else
    {
        DEBUG((DEBUG_ERROR, "[AdiPkg] : Protocol NOT Installed =>  %r\n", status));
    }
    return EFI_SUCCESS;
}