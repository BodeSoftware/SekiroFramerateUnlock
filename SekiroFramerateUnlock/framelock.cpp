#include <windows.h>
#include <cstdint>
#include "offsets.h"
#include "memory_helpers.h"
#include "ini_config.h"

// The core patch function
void ApplyFramelockPatch()
{
    // Load settings from INI file
    IniConfig config("SekiroFPS.ini");

    // Create default INI if it doesn't exist
    config.CreateDefault();

    // Read settings
    float DESIRED_FPS = config.GetFloat("Settings", "TargetFPS", 144.0f);

    uintptr_t fps_addr = GetAbsoluteAddress(fps_offset);
    if (!fps_addr) {
        MessageBoxA(nullptr, "Failed to compute fps address", "Framelock", MB_OK | MB_ICONERROR);
        return;
    }

    float FPS = DESIRED_FPS;
    // clamp to a sensible range
    if (FPS < 30.0f) FPS = 30.0f;
    if (FPS > 300.0f) FPS = 300.0f;

    float targetDelta = 1.0f / FPS;

    if (!WriteProtectedMemory(fps_addr, &targetDelta, sizeof(targetDelta))) {
        MessageBoxA(nullptr, "Framelock patch failed (write error)", "Framelock", MB_OK | MB_ICONERROR);
        return;
    }
}