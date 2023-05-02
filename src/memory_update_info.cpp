#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <cmath>
#include "functions_and_global_variables.h"

bool memory_update_info(MEMORYSTATUSEX& statex)
{
    double size_pagefile_on_disk;
    double available_pagefile_on_disk;

    while (!_kbhit())
    {
        clear_screen();

        GlobalMemoryStatusEx(&statex);      // update RAM info

        size_pagefile_on_disk = (statex.ullTotalPageFile - statex.ullTotalPhys) / B_to_GB;

        if (statex.ullAvailPageFile < statex.ullAvailPhys)
            available_pagefile_on_disk = statex.ullAvailPageFile / B_to_GB;
        else
            available_pagefile_on_disk = (statex.ullAvailPageFile - statex.ullAvailPhys) / B_to_GB;

        printf("\n\n\tSize of pagefile:      %.2lf GB", size_pagefile_on_disk                           );
        printf("\n\n\tIn use in pagefile:    %.2lf GB", size_pagefile_on_disk - available_pagefile_on_disk);
        printf(  "\n\tAvailable in pagefile: %.2lf GB", available_pagefile_on_disk                        );

        printf("\n\n\n");
        printf("\tRAM in use:    %.2lf GB --- %hu %%\n", (statex.ullTotalPhys - statex.ullAvailPhys) / B_to_GB,       statex.dwMemoryLoad);
        printf("\tRAM available: %.2lf GB --- %hu %%\n",  statex.ullAvailPhys / B_to_GB,                        100 - statex.dwMemoryLoad);

        printf("\n\n\tPress [spacebar] for RESTART or [any other key] to END the program and clear the memory\n");

        Sleep(500);

    }

    if (_getch() == key_spacebar)
        return true;

    else
        return false;
}

bool memory_update_info_without_pagefile(MEMORYSTATUSEX& statex)
{
    while (!_kbhit())
    {
        clear_screen();

        GlobalMemoryStatusEx(&statex);      // update RAM info

        printf("\n\n\tRAM in use:    %.2lf GB --- %hu %%\n", (statex.ullTotalPhys - statex.ullAvailPhys) / B_to_GB,       statex.dwMemoryLoad);
        printf(    "\tRAM available: %.2lf GB --- %hu %%\n",  statex.ullAvailPhys / B_to_GB,                        100 - statex.dwMemoryLoad);

        printf("\n\n\tPress [spacebar] for RESTART or [any other key] to END the program and clear the memory\n");

        Sleep(500);
    }

    if (_getch() == key_spacebar)
        return true;

    else
        return false;
}