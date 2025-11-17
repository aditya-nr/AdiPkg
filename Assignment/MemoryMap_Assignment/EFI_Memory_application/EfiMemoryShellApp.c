#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Pi/PiDxeCis.h>

EFI_STATUS
EFIAPI
EfiMemoryShellAppEntryPoint(
    EFI_HANDLE ImgHandle,
    EFI_SYSTEM_TABLE *gST)
{
    DEBUG((DEBUG_ERROR, "[AdiPkg] : EfiMemoryShellAppEntryPoint\n"));
    EFI_BOOT_SERVICES *gBS = gST->BootServices;
    EFI_STATUS Status;

    UINTN MemoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *MemoryMap = NULL;
    UINTN MapKey;
    UINTN DescriptorSize;
    UINT32 DescriptorVersion;

    // query MemoryMapSize
    Status = gBS->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (Status != EFI_BUFFER_TOO_SMALL)
    {
        DEBUG((DEBUG_ERROR, "[AdiPkg] : query MemoryMapSize Failed | Status : %r\n", Status));
        return Status;
    }
    DEBUG((DEBUG_ERROR, "[AdiPkg] : Status : %r\n MemoryMapSize : %u \n MapKey : %u \n DescriptorSize : %u\n DescriptorVersion : %u \n", Status, MemoryMapSize, MapKey, DescriptorSize, DescriptorVersion));
    // Allocate Memory
    MemoryMapSize += 2 * DescriptorSize;
    Status = gBS->AllocatePool(EfiLoaderData, MemoryMapSize, (void **)&MemoryMap);
    if (EFI_ERROR(Status) != 0)
    {
        DEBUG((DEBUG_ERROR, "[AdiPkg] : Allocate Memory Failed | Status : %r\n", Status));
        return Status;
    }

    // get MemoryMap
    Status = gBS->GetMemoryMap(&MemoryMapSize, MemoryMap, &MapKey, &DescriptorSize, &DescriptorVersion);
    if (Status != EFI_SUCCESS)
    {
        gBS->FreePool(MemoryMap);
        DEBUG((DEBUG_ERROR, "[AdiPkg] : getMemoryMap Failed | Status : %r\n", Status));
        return Status;
    }

    DEBUG((DEBUG_ERROR, "[AdiPkg] : Status : %r\n MemoryMapSize : %u \n MapKey : %u \n DescriptorSize : %u\n DescriptorVersion : %u \n", Status, MemoryMapSize, MapKey, DescriptorSize, DescriptorVersion));

    gBS->FreePool(MemoryMap);
    return EFI_SUCCESS;
}