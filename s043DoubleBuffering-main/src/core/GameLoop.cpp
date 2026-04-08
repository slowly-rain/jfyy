#include "../common.h"

void initConsoleBuffers() {
    if (hOutput1 != INVALID_HANDLE_VALUE) CloseHandle(hOutput1);
    if (hOutput2 != INVALID_HANDLE_VALUE) CloseHandle(hOutput2);
    hOutput1 = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    hOutput2 = CreateConsoleScreenBuffer(GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
    CONSOLE_CURSOR_INFO cci;
    cci.bVisible = FALSE;
    cci.dwSize = 1;
    SetConsoleCursorInfo(hOutput1, &cci);
    SetConsoleCursorInfo(hOutput2, &cci);
    SetConsoleActiveScreenBuffer(hOutput1);
}

void restoreDefaultBuffer() {
    SetConsoleActiveScreenBuffer(GetStdHandle(STD_OUTPUT_HANDLE));
    if (hOutput1 != INVALID_HANDLE_VALUE) CloseHandle(hOutput1);
    if (hOutput2 != INVALID_HANDLE_VALUE) CloseHandle(hOutput2);
    hOutput1 = hOutput2 = INVALID_HANDLE_VALUE;
}