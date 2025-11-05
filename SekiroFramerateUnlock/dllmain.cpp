#include <Windows.h>
#include "offsets.h"
#include "memory_helpers.h"

// Forward declarations
void ApplyFramelockPatch(); // from framelock.cpp
extern "C" BOOL LoadOriginalD3DCompiler();
extern "C" void FreeOriginalD3DCompiler();

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DisableThreadLibraryCalls(hModule);
        LoadOriginalD3DCompiler(); // load the real system DLL first

        // Run our patch after game initialization
        CreateThread(nullptr, 0, [](LPVOID) -> DWORD {
            Sleep(1500); // small delay to avoid early memory writes
            ApplyFramelockPatch();
            return 0;
            }, nullptr, 0, nullptr);
        break;

    case DLL_PROCESS_DETACH:
        FreeOriginalD3DCompiler();
        break;
    }
    return TRUE;
}
