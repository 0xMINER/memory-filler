#pragma once
#include <windows.h>
#include <conio.h>
#include <cstdint>

enum value_char
{
    key_spacebar = 32,
    key_one = 49,
    key_two = 50
};

inline constexpr FLOAT B_to_GB = 1073741824.;    // from BYTES to GIGABYTES
inline constexpr uint16_t page_size = 0x1000;    // standart page size on PC, 4096 bytes

inline void* starting_address_VirtualAlloc = {}; // pointer to start of allocated memory

bool memory_update_info(MEMORYSTATUSEX& statex);
bool memory_update_info_without_pagefile(MEMORYSTATUSEX& statex);
bool memory_filler(uint64_t* total_RAM, DWORD* percent_of_RAM_in_use, MEMORYSTATUSEX& statex);

void clear_screen();
void exception_handler();