#include <windows.h>
#include <conio.h>
#include <cstdio>
#include <cmath>
#include "functions_and_global_variables.h"

int main(int argc, char* argv[])
{
    MEMORYSTATUSEX statex = {};
    statex.dwLength = sizeof(statex);

    bool restart_main = false;

    do
    {
        restart_main = false;

        while (!_kbhit())
        {
            clear_screen();

            GlobalMemoryStatusEx(&statex); // update RAM info

            printf("\n\n");
            printf("\tIn system      %.0lf GB RAM       \n\n", round (statex.ullTotalPhys / B_to_GB));
            printf("\tRAM in use:    %.2lf GB -- %2hu %%\n",   round((statex.ullTotalPhys - statex.ullAvailPhys) / B_to_GB * 100) / 100,       statex.dwMemoryLoad);
            printf("\tRAM available: %.2lf GB -- %2hu %%\n\n", round (statex.ullAvailPhys / B_to_GB * 100) / 100,                        100 - statex.dwMemoryLoad);

            printf("\n\t[spacebar] or [1] - memory fill WITH pagefile monitoring");
            printf("\n\t              [2] - memory fill WITHOUT pagefile monitoring");
            printf("\n\n\t-> ");

            Sleep(500);
        }

        switch (_getch())
        {
        case key_spacebar:
        case key_one:

            if (memory_loader(&statex.ullTotalPhys, &statex.dwMemoryLoad, statex))
                restart_main = true;

            else
                restart_main = memory_update_info(statex);

            break;

        case key_two:

            if (memory_loader(&statex.ullTotalPhys, &statex.dwMemoryLoad, statex))
                restart_main = true;

            else
                restart_main = memory_update_info_without_pagefile(statex);

            break;

        default:

            clear_screen();
            printf("\n\tIncorrect input. Enter [spacebar] or [1] or [2]\n");

            restart_main = true;

            Sleep(2500);
        }

        if (starting_address_VirtualAlloc == NULL)
        {
            printf("\n\n\tUNKNOWN_EXCEPTION: starting address from VirtualAlloc == NULL");
            return 1;
        }

        VirtualFree(starting_address_VirtualAlloc, 0, MEM_RELEASE);

        starting_address_VirtualAlloc = {};
    } while (restart_main);

    return 0;
}