#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Protocol/PciIo.h>

extern EFI_GUID gEfiPciIoProtocolGuid;

EFI_STATUS
EFIAPI
EntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *gST)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] : PcieInfo_EntryPoint ================\n"));
    EFI_STATUS Status;
    EFI_BOOT_SERVICES *gBS;
    gBS = gST->BootServices;

    UINTN NoOfHandles;
    EFI_HANDLE *HandleArray = NULL;

    Status = gBS->LocateHandleBuffer(
        ByProtocol,
        &gEfiPciIoProtocolGuid,
        NULL,
        &NoOfHandles,
        &HandleArray);

    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] : Unable to get all the handles \n Status : %d\n", Status));
        return EFI_NOT_FOUND;
    }

    EFI_PCI_IO_PROTOCOL *EfiPciIoProtocol;
    for (int index = 0; index < NoOfHandles; index++)
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] :Handle [%d] : %p\n", index + 1, HandleArray[index]));
        Status = gBS->HandleProtocol(HandleArray[index], &gEfiPciIoProtocolGuid, (void **)&EfiPciIoProtocol);

        if (!EFI_ERROR(Status))
        {
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
                DEBUG((DEBUG_INFO, "    Seg Bus Dev Func : %d %d %d %d\n", SegmentNumber, BusNumber, DeviceNumber, FunctionNumber));
            }
        }
        else
        {
            DEBUG((DEBUG_INFO, "    Error Getting Rom Size | Status : %u\n", Status));
        }
    }

    return EFI_SUCCESS;
}
