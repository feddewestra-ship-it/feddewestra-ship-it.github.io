#include <efi.h>
#include <efilib.h>

#define MIN_RAM_MB 128

void crash(EFI_SYSTEM_TABLE *SystemTable, CHAR16 *reason)
{
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"GEFAALD: ");
    SystemTable->ConOut->OutputString(SystemTable->ConOut, reason);
    SystemTable->ConOut->OutputString(SystemTable->ConOut, L"\n");

    while (1)
    {
        __asm__("hlt");
    }
}

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    Print(L"NexoOS build 000.001\n");
    Print(L"Hardware controle...\n");

    EFI_BOOT_SERVICES *BootServices = SystemTable->BootServices;

    UINTN memoryMapSize = 0;
    EFI_MEMORY_DESCRIPTOR *memoryMap = NULL;
    UINTN mapKey;
    UINTN descriptorSize;
    UINT32 descriptorVersion;

    BootServices->GetMemoryMap(
        &memoryMapSize,
        memoryMap,
        &mapKey,
        &descriptorSize,
        &descriptorVersion
    );

    memoryMapSize += descriptorSize * 10;

    BootServices->AllocatePool(
        EfiLoaderData,
        memoryMapSize,
        (void**)&memoryMap
    );

    BootServices->GetMemoryMap(
        &memoryMapSize,
        memoryMap,
        &mapKey,
        &descriptorSize,
        &descriptorVersion
    );

    UINT64 totalRAM = 0;

    for (UINTN i = 0; i < memoryMapSize / descriptorSize; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc =
            (EFI_MEMORY_DESCRIPTOR*)((UINT8*)memoryMap + (i * descriptorSize));

        totalRAM += desc->NumberOfPages * 4096;
    }

    UINT64 ramMB = totalRAM / (1024 * 1024);

    if (ramMB < MIN_RAM_MB)
    {
        crash(SystemTable, L"te weinig RAM");
    }

    Print(L"RAM OK\n");
    Print(L"NexoOS boot kan doorgaan.\n");

    while (1)
    {
        __asm__("hlt");
    }

    return EFI_SUCCESS;
}
