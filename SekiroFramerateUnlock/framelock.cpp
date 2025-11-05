#include <windows.h>
#include <cstdint>
#include "offsets.h"
#include "memory_helpers.h"

// Simple settings: choose desired FPS here (or read from an ini if you want)
static float DESIRED_FPS = 144.0f; // change to whatever you want
static bool ENABLED = true;        // set false to restore 60 FPS on write

// The core patch function
void ApplyFramelockPatch()
{
    uintptr_t fps_addr = GetAbsoluteAddress(fps_offset);
    if (!fps_addr) {
        MessageBoxA(nullptr, "Failed to compute fps address", "Framelock", MB_OK | MB_ICONERROR);
        return;
    }

    float FPS = DESIRED_FPS;
    // clamp to a sensible range
    if (FPS < 30.0f) FPS = 30.0f;
    if (FPS > 300.0f) FPS = 300.0f;

    if (!ENABLED)
        FPS = 60.0f;

    float targetDelta = 1.0f / FPS;

    if (!WriteProtectedMemory(fps_addr, &targetDelta, sizeof(targetDelta))) {
        MessageBoxA(nullptr, "Framelock patch failed (write error)", "Framelock", MB_OK | MB_ICONERROR);
        return;
    }
}