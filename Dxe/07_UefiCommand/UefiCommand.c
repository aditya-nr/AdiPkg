#include <Uefi.h>
#include <Library/UefiLib.h>
#include <Library/DebugLib.h>
#include <Protocol/ShellDynamicCommand.h>
#include <Library/MemoryAllocationLib.h>

SHELL_STATUS
EFIAPI ShellCommandHandler(
    IN EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL *This,
    IN EFI_SYSTEM_TABLE *SystemTable,
    IN EFI_SHELL_PARAMETERS_PROTOCOL *ShellParameters,
    IN EFI_SHELL_PROTOCOL *Shell)
{
    Print(L"Hello Custom Shell Command\n");
    return SHELL_SUCCESS;
}

CHAR16 *
    EFIAPI
    ShellCommandHelp(
        IN EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL *This,
        IN CONST CHAR8 *Language)
{
    CHAR16 *HelpString = L"MyCommand: Prints a greeting.\n";
    UINTN Size = StrSize(HelpString);
    CHAR16 *Copy = AllocateCopyPool(Size, HelpString);
    return Copy;
}

static EFI_SHELL_DYNAMIC_COMMAND_PROTOCOL mEfiShellDynamicCommandProtocol = {
    L"sayhello",
    &ShellCommandHandler,
    &ShellCommandHelp};

EFI_STATUS EFIAPI
EntryPoint(IN EFI_HANDLE ImageHandle, IN EFI_SYSTEM_TABLE *gST)
{
    DEBUG((DEBUG_INFO, "[AdiPkg] : UefiCommand_EntryPoint ================\n"));
    EFI_STATUS Status;
    EFI_BOOT_SERVICES *gBS;
    gBS = gST->BootServices;

    Status = gBS->InstallProtocolInterface(
        &ImageHandle,
        &gEfiShellDynamicCommandProtocolGuid,
        EFI_NATIVE_INTERFACE,
        (void *)&mEfiShellDynamicCommandProtocol);

    if (EFI_ERROR(Status))
    {
        DEBUG((DEBUG_INFO, "[AdiPkg] : Unable to Install command protocol \n Status : %d\n", Status));
        return Status;
    }

    return EFI_SUCCESS;
}
