#include <Uefi.h>
#include <Library/DebugLib.h>
#include <Library/PrintLib.h>
#include <Protocol.h>

EFI_GUID gPrintHelloProtoGuid = PRINT_HELLO_PROTO_GUID;

EFI_STATUS
EFIAPI
EntryPoint(
    IN EFI_HANDLE ImageHandle,
    IN EFI_SYSTEM_TABLE *gST)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] : GetProtocol EntryPoint\n"));

    EFI_STATUS Status;
    EFI_BOOT_SERVICES *gBS = NULL;
    EFI_RUNTIME_SERVICES *gRS = NULL;
    PRINT_HELLO_PROTOCOL *PrintHelloProtocol = NULL;

    gBS = gST->BootServices;

    /**
     * Using LocateProtocol
     */
    Status = gBS->LocateProtocol(&gPrintHelloProtoGuid, NULL, (void **)&PrintHelloProtocol);
    if (!EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateProtocol) Protocol Found, Calling Print() \n"));
        PrintHelloProtocol->Print();
        DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateProtocol) INTERFACE Address : %p \n", PrintHelloProtocol));
    }
    else
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateProtocol) Protocol NOT Found : \n[STATUS] : %r \n", Status));
    }

    /**
     * Using LocateHandle()
     */
    UINTN NoOfHandles;
    EFI_HANDLE *HandleArray = NULL;
    Status = gBS->LocateHandleBuffer(ByProtocol, &gPrintHelloProtoGuid, NULL, &NoOfHandles, &HandleArray);
    if (!EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateHandle ByProtocol) Handle Found => NoOfHandles = %d \n", NoOfHandles));
        for (int index = 0; index < NoOfHandles; index++)
        {
            DEBUG((DEBUG_INFO, "[AdiPkg] : Handle [%d] =  %p \n", index, HandleArray[index]));
        }
    }
    else
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateHandle ByProtocol) Protocol NOT Found : \n[STATUS] : %r \n", Status));
    }

    /**
     * Using LocateHandle() ALL
     */
    // Status = gBS->LocateHandleBuffer(AllHandles, NULL, NULL, &NoOfHandles, &HandleArray);
    // if (!EFI_ERROR(Status))
    // {
    //     DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateHandle ALL) Handle Found => NoOfHandles = %d \n", NoOfHandles));
    //     for (int index = 0; index < NoOfHandles; index++)
    //     {
    //         DEBUG((DEBUG_INFO, "[AdiPkg] : Handle [%d] =  %p \n", index, HandleArray[index]));
    //     }
    // }
    // else
    // {
    //     DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateHandle ALL) Protocol NOT Found : \n[STATUS] : %r \n", Status));
    // }

    /**
     * All the PROTOCOLS of ALL the HANDLES | Using LocateHandle() and HandleProtocol()
     */
    Status = gBS->LocateHandleBuffer(AllHandles, NULL, NULL, &NoOfHandles, &HandleArray);
    if (!EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] : \"All The Protocols of All the Handles\" | NoOfHandles = %d \n", NoOfHandles));
        for (int index = 0; index < NoOfHandles; index++)
        {
            DEBUG((DEBUG_INFO, "[AdiPkg] : Handle [%d] =  %p \n", index, HandleArray[index]));

            EFI_GUID **ProtocolGuidArray = NULL;
            UINTN NoOfGuids;
            Status = gBS->ProtocolsPerHandle(HandleArray[index], &ProtocolGuidArray, &NoOfGuids);
            if (!EFI_ERROR(Status))
            {
                DEBUG((DEBUG_INFO, "[AdiPkg] :      No Of Protocols =  %d \n", NoOfGuids));
                for (int index2 = 0; index2 < NoOfGuids; index2++)
                {
                    CHAR16 GuidStr[100];
                    UnicodeSPrint(GuidStr, sizeof(GuidStr), L"%g", ProtocolGuidArray[index2]);
                    DEBUG((DEBUG_INFO, "[AdiPkg] :          Protocol [%u] = %s\n", index2, GuidStr));
                }

                // free the protocol list
                if (ProtocolGuidArray != NULL)
                    gBS->FreePool(ProtocolGuidArray);
            }
            else
            {
                DEBUG((DEBUG_INFO, "[AdiPkg] : ProtocolPerGuid Failed : \n[STATUS] : %r \n", Status));
            }
        }

        // Free the handleBuffer
        if (HandleArray != NULL)
        {
            gBS->FreePool(HandleArray);
        }
    }
    else
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] :(Using LocateHandle ALL) Protocol NOT Found : \n[STATUS] : %r \n", Status));
    }

    return EFI_SUCCESS;
}
