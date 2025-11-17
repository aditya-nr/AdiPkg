#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Protocol/DriverBinding.h>
#include <Library/UefiBootServicesTableLib.h>
#include <Protocol/PciIo.h>

EFI_STATUS
EFIAPI Supported(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] :Support is called for : %p\n", ControllerHandle));
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *EfiPciIoProtocol = NULL;
    Status = gBS->HandleProtocol(
        ControllerHandle,
        &gEfiPciIoProtocolGuid,
        (void **)&EfiPciIoProtocol);

    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] :      UNSUPPORTED | Status : %u\n", Status));
        return Status;
    }
    DEBUG((DEBUG_INFO, "[AdiPkg] :      SUPPORTED...\n"));
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI Start(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE ControllerHandle,
    IN EFI_DEVICE_PATH_PROTOCOL *RemainingDevicePath OPTIONAL)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] : Start is called for : %p\n", ControllerHandle));
    EFI_STATUS Status;
    EFI_PCI_IO_PROTOCOL *EfiPciIoProtocol = NULL;
    Status = gBS->HandleProtocol(
        ControllerHandle,
        &gEfiPciIoProtocolGuid,
        (void **)&EfiPciIoProtocol);

    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "[AdiPkg] :      Error to get protocol | Status : %r\n", Status));
        return Status;
    }

    // ROM SIZE
    UINTN romSize = EfiPciIoProtocol->RomSize;
    DEBUG((DEBUG_INFO, "    Rom Size : %u\n", romSize));

    // BDF number
    UINTN SegmentNumber, BusNumber, DeviceNumber, FunctionNumber;
    Status = EfiPciIoProtocol->GetLocation(
        EfiPciIoProtocol,
        &SegmentNumber,
        &BusNumber,
        &DeviceNumber,
        &FunctionNumber);
    if (!EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "    Seg Bus Dev Func : %u %u %u %u\n", SegmentNumber, BusNumber, DeviceNumber, FunctionNumber));
    }

    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI Stop(
    IN EFI_DRIVER_BINDING_PROTOCOL *This,
    IN EFI_HANDLE ControllerHandle,
    IN UINTN NumberOfChildren,
    IN EFI_HANDLE *ChildHandleBuffer OPTIONAL)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] :Stop is called for : %p\n", ControllerHandle));
    return EFI_SUCCESS;
}

EFI_DRIVER_BINDING_PROTOCOL mDriverBindingProtocol = {
    &Supported,
    &Start,
    &Stop,
    0x1,
    NULL,
    NULL};

EFI_STATUS
EFIAPI GetDriverName(
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN CHAR8 *Language,
    OUT CHAR16 **DriverName)
{
    *DriverName = L"AdiPkg_Driver";
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI GetControllerName(
    IN EFI_COMPONENT_NAME_PROTOCOL *This,
    IN EFI_HANDLE ControllerHandle,
    IN EFI_HANDLE ChildHandle OPTIONAL,
    IN CHAR8 *Language,
    OUT CHAR16 **ControllerName)
{
    *ControllerName = L"AdiPkg_Controller";
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI GetDriverName2(
    IN EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN CHAR8 *Language,
    OUT CHAR16 **DriverName)
{
    *DriverName = L"AdiPkg_DriverN2";
    return EFI_SUCCESS;
}

EFI_STATUS
EFIAPI GetControllerName2(
    IN EFI_COMPONENT_NAME2_PROTOCOL *This,
    IN EFI_HANDLE ControllerHandle,
    IN EFI_HANDLE ChildHandle OPTIONAL,
    IN CHAR8 *Language,
    OUT CHAR16 **ControllerName)
{
    *ControllerName = L"AdiPkg_ControllerN2";
    return EFI_SUCCESS;
}

CHAR8 langs[] = "eng\0\0";

CHAR8 langs2[] = "en\0\0";

EFI_COMPONENT_NAME_PROTOCOL mComponentNameProtocol = {
    &GetDriverName,
    &GetControllerName,
    langs};

EFI_COMPONENT_NAME2_PROTOCOL mComponentName2Protocol = {
    &GetDriverName2,
    &GetControllerName2,
    langs2};

EFI_STATUS EFIAPI
EntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *gST)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] : DBind1_EntryPoint ================\n"));
    EFI_STATUS Status;

    Status = EfiLibInstallDriverBindingComponentName2(
        ImageHandle,
        gST,
        &mDriverBindingProtocol,
        ImageHandle,
        &mComponentNameProtocol,
        &mComponentName2Protocol);

    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_ERROR, "[AdiPkg] : Unable to Install binding protocol \n Status : %r\n", Status));
        return Status;
    }

    return EFI_SUCCESS;
}
