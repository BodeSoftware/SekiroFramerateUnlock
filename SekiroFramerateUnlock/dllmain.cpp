#include <Windows.h>
#include "offsets.h"
#include "memory_helpers.h"

// Forward declarations
void ApplyFramelockPatch(); // from framelock.cpp
void ForceBorderlessWindow(); // helper to make Sekiro borderless

extern "C" BOOL LoadOriginalD3DCompiler();
extern "C" void FreeOriginalD3DCompiler();

// ------------------------------------------------------------
// Helper function: Forces Sekiro into borderless window mode
// ------------------------------------------------------------
void ForceBorderlessWindow()
{
    // Wait a moment for the game window to be created
    Sleep(2000);

    HWND hwnd = FindWindowA(nullptr, "Sekiro"); // window title
    if (!hwnd)
        return;

    // Get full screen resolution
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);

    // Remove all borders, title bar, resizing, etc.
    LONG style = GetWindowLong(hwnd, GWL_STYLE);
    style &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
    SetWindowLong(hwnd, GWL_STYLE, style);

    LONG exStyle = GetWindowLong(hwnd, GWL_EXSTYLE);
    exStyle &= ~(WS_EX_DLGMODALFRAME | WS_EX_WINDOWEDGE | WS_EX_CLIENTEDGE | WS_EX_STATICEDGE);
    SetWindowLong(hwnd, GWL_EXSTYLE, exStyle);

    // Resize and position window to cover the full screen
    SetWindowPos(hwnd, HWND_TOP,
        0, 0, screenWidth, screenHeight,
        SWP_NOOWNERZORDER | SWP_FRAMECHANGED | SWP_SHOWWINDOW);
}

// ------------------------------------------------------------
// DllMain: entry point for the DLL
// ------------------------------------------------------------
BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        LoadOriginalD3DCompiler(); // load the real system DLL first

        // Run our patch and borderless fix after game initialization
        CreateThread(nullptr, 0, [](LPVOID) -> DWORD {
            Sleep(1500); // small delay to avoid early memory writes
            ApplyFramelockPatch();
            ForceBorderlessWindow();
            return 0;
            }, nullptr, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        FreeOriginalD3DCompiler();
        break;
    }
    return TRUE;
}
