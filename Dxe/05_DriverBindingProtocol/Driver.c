#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/DriverBinding.h>
#include <Header.h>
#include <Library/DebugLib.h>

EFI_GUID gMyDeviceProtocolGuid = MY_DEVICE_PROTO_GUID;

// Forward declarations
EFI_STATUS EFIAPI MyDriverSupported(IN EFI_DRIVER_BINDING_PROTOCOL *This, IN EFI_HANDLE Controller, IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL);
EFI_STATUS EFIAPI MyDriverStart(IN EFI_DRIVER_BINDING_PROTOCOL *This, IN EFI_HANDLE Controller, IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL);
EFI_STATUS EFIAPI MyDriverStop(IN EFI_DRIVER_BINDING_PROTOCOL *This, IN EFI_HANDLE Controller, IN UINTN NumberOfChildren, IN EFI_HANDLE *ChildHandleBuffer OPTIONAL);

EFI_DRIVER_BINDING_PROTOCOL gMyDriverBinding = {
    MyDriverSupported,
    MyDriverStart,
    MyDriverStop,
    0x10,
    NULL,
    NULL};

EFI_STATUS
EFIAPI
MyDriverSupported(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE Controller,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] : Driver support called\n Controller : %p\n DriverBindingHandle : %p\n", Controller, This->DriverBindingHandle));
    EFI_STATUS Status;
    VOID *MyDevice;

    Status = gBS->OpenProtocol(
        Controller,
        &gMyDeviceProtocolGuid,
        &MyDevice,
        This->DriverBindingHandle,
        Controller,
        EFI_OPEN_PROTOCOL_BY_DRIVER);

    if (EFI_ERROR(Status))
    {
        return Status;
    }
    DEBUG((DEBUG_INFO, "[AdiPkg] : THIS DEVICE SUPPORTS \n MyDevice : %p\n Status : %p\n", MyDevice, Status));
    gBS->CloseProtocol(Controller, &gMyDeviceProtocolGuid, This->DriverBindingHandle, Controller);
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MyDriverStart(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE Controller,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL)
{
    Print(L"MyDriver started for handle %p\n", Controller);
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
MyDriverStop(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE Controller,
    IN UINTN NumberOfChildren,
    IN EFI_HANDLE *ChildHandleBuffer OPTIONAL)
{
    Print(L"MyDriver stopped for handle %p\n", Controller);
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI
EntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] : Driver Entry Point\n"));
    return EfiLibInstallDriverBindingComponentName2(
        ImageHandle,
        SystemTable,
        &gMyDriverBinding,
        ImageHandle,
        NULL,
        NULL);
}
