#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Protocol/DevicePath.h>
#include <Header.h>

EFI_GUID gMyDeviceProtocolGuid = MY_DEVICE_PROTO_GUID;
const EFI_GUID gMyDevicePathGuid = MY_DEVICE_PATH_GUID;

EFI_STATUS
EFIAPI
EntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *SystemTable)
{
    EFI_STATUS Status;
    EFI_HANDLE DeviceHandle = NULL;
    static MY_DEVICE_PROTOCOL MyDevice = {1234};
    EFI_BOOT_SERVICES *gBS = SystemTable->BootServices;

    // Build a simple device path
    static MY_DEVICE_PATH MyDevicePath = {
        {{HARDWARE_DEVICE_PATH, HW_VENDOR_DP, {(UINT8)(sizeof(VENDOR_DEVICE_PATH)), (UINT8)(sizeof(VENDOR_DEVICE_PATH) >> 8)}},
         gMyDevicePathGuid},
        {END_DEVICE_PATH_TYPE, END_ENTIRE_DEVICE_PATH_SUBTYPE, {sizeof(EFI_DEVICE_PATH_PROTOCOL), 0}}};

    Status = gBS->InstallProtocolInterface(
        &DeviceHandle,
        &gMyDeviceProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &MyDevice);
    Status = gBS->InstallProtocolInterface(
        &DeviceHandle,
        &gEfiDevicePathProtocolGuid,
        EFI_NATIVE_INTERFACE,
        &MyDevicePath);

    if (EFI_ERROR(Status))
    {
        // Print(L"Failed to install MyDevice protocol: %r\n", Status);
        DEBUG((DEBUG_INFO, "[AdiPkg] : Failed to install MyDevice protocol: %r\n", Status));
        return Status;
    }

    // Print(L"MyDevice installed on handle %p\n", DeviceHandle);
    DEBUG((DEBUG_INFO, "[AdiPkg] : MyDevice installed\n handle : %p\n protocol : %p \n", DeviceHandle, &MyDevice));
    return EFI_SUCCESS;
}
