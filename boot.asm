#include <efi.h>
#include <efilib.h>

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    Print(L"NexoOS build 000.001\n");
    Print(L"UEFI bootloader gestart.\n");

    while (1)
    {
        __asm__("hlt");
    }

    return EFI_SUCCESS;
}
