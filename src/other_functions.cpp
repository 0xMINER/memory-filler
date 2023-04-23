#include <windows.h>
#include <cstdio>
#include "functions_and_global_variables.h"

void exception_handler()
{
    printf("ERROR: starting address for VirtualAlloc == nullptr | ");
    GetLastError() == 87 ? printf("ERROR_INVALID_PARAMETER") : printf("%s %lu %s", "UNKNOWN_EXCEPTION: GetLastError() return [", GetLastError(), "]");
    system("pause");
}

void clear_screen()
{
    CONSOLE_SCREEN_BUFFER_INFO screen_buffer;
    HANDLE console_handle = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD  top_left = { 0, 0 };
    DWORD  ñhars;

    GetConsoleScreenBufferInfo(console_handle, &screen_buffer);
    FillConsoleOutputCharacterA(console_handle, ' ', screen_buffer.dwSize.X * screen_buffer.dwSize.Y, top_left, &ñhars);
    SetConsoleCursorPosition(console_handle, top_left);
}