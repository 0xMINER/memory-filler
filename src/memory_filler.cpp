#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <cinttypes>
#include "functions_and_global_variables.h"

bool memory_filler(const uint64_t* total_RAM, const DWORD* percent_of_RAM_in_use, MEMORYSTATUSEX& statex)
{
    uint8_t target_percents = 0;
    bool restart_memory_filler = false;

    do 
    {
        clear_screen();

        restart_memory_filler = false;

        GlobalMemoryStatusEx(&statex);  // update RAM info

        printf("\n\n\tIn use: %hu %% RAM", *percent_of_RAM_in_use);

        printf("\n\tEnter target %% RAM load -> ");
        scanf_s("%" PRId8, &target_percents);    // target % of RAM load

        clear_screen();

        if (target_percents > 100)
        {
            printf("\n\tERROR_COMMITMENT_LIMIT");
            printf("\n\tWas entered >100 %%\n");

            restart_memory_filler = true;
            Sleep(3000);
        }

        else if (target_percents <= *percent_of_RAM_in_use)
        {
            printf("\n\ttWas entered <= %% RAM usage\n");

            restart_memory_filler = true;
            Sleep(3000);
        }

        else 
            continue;
    } while (restart_memory_filler);

    GlobalMemoryStatusEx(&statex);  // update RAM info

    const uint64_t one_percent_of_RAM_in_b = *total_RAM / 100;                                                         // 1% of all RAM in bytes
    const uint8_t  difference_percents     = target_percents - static_cast<uint8_t>(*percent_of_RAM_in_use);           // additional loading to target %
    const uint64_t memory_load_data_size   = one_percent_of_RAM_in_b * difference_percents;                            // amount of data to be loaded in bytes

    starting_address_VirtualAlloc = VirtualAlloc(nullptr, memory_load_data_size, MEM_COMMIT, PAGE_READWRITE);    // creating allocated memory

    if (starting_address_VirtualAlloc == nullptr)
    {
        exception_handler();
        return true;
    }

    else
    {
        char* ptr = static_cast<char*>(starting_address_VirtualAlloc);   // pointer to start of allocated memory

        for (uint64_t i = 0; i < memory_load_data_size; i += page_size)  // writing at the beginning of every page
            ptr[i]++;

        return false;
    }
}