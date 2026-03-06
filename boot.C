#include <efi.h>
#include <efilib.h>

#define MIN_RAM_MB 128

EFI_STATUS efi_main(EFI_HANDLE ImageHandle, EFI_SYSTEM_TABLE *SystemTable)
{
    InitializeLib(ImageHandle, SystemTable);

    Print(L"NexoOS build 000.001\n");
    Print(L"Hardware controle gestart...\n\n");

    EFI_BOOT_SERVICES *BootServices = SystemTable->BootServices;

    /* ============================= */
    /* RAM CHECK                     */
    /* ============================= */

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

    for(UINTN i = 0; i < memoryMapSize / descriptorSize; i++)
    {
        EFI_MEMORY_DESCRIPTOR *desc = (EFI_MEMORY_DESCRIPTOR*)
            ((UINT8*)memoryMap + (i * descriptorSize));

        totalRAM += desc->NumberOfPages * 4096;
    }

    UINT64 ramMB = totalRAM / (1024 * 1024);

    Print(L"Gevonden RAM: %d MB\n", ramMB);

    if(ramMB < MIN_RAM_MB)
    {
        Print(L"FOUT: onvoldoende RAM!\n");
        Print(L"NexoOS kan niet starten.\n");

        while(1)
        {
            __asm__("hlt");
        }
    }

    Print(L"RAM controle OK\n");

    /* ============================= */
    /* CONSOLE CHECK                 */
    /* ============================= */

    if(SystemTable->ConOut == NULL)
    {
        while(1)
        {
            __asm__("hlt");
        }
    }

    Print(L"Console OK\n");

    /* ============================= */
    /* OPSLAG CHECK (placeholder)    */
    /* ============================= */

    Print(L"Opslag: verwacht FAT32 EFI boot pad\n");

    /* ============================= */
    /* RESULTAAT                     */
    /* ============================= */

    Print(L"\nHardware compatibel.\n");
    Print(L"NexoOS boot kan doorgaan.\n");

    while(1)
    {
        __asm__("hlt");
    }

    return EFI_SUCCESS;
}
