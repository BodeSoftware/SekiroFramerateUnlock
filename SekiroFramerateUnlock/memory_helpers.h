#pragma once
#include <cstdint>
#include <windows.h>

// Convert offset (RVA) to an absolute address in this process' module.
// This assumes the offset is relative to the module base (typical for game mods).
inline uintptr_t GetAbsoluteAddress(uintptr_t offset) {
    HMODULE hModule = GetModuleHandle(nullptr); // Sekiro.exe module
    if (!hModule) return 0;
    return reinterpret_cast<uintptr_t>(hModule) + offset;
}

// WriteProtectedMemory: temporarily change page protection and copy bytes
inline bool WriteProtectedMemory(uintptr_t address, const void* data, size_t size) {
    if (!address || !data || size == 0) return false;
    DWORD oldProt = 0;
    if (!VirtualProtect(reinterpret_cast<LPVOID>(address), size, PAGE_EXECUTE_READWRITE, &oldProt))
        return false;
    memcpy(reinterpret_cast<void*>(address), data, size);
    // flush instruction/data cache (not always necessary for data writes but safe)
    FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<LPCVOID>(address), size);
    DWORD tmp;
    VirtualProtect(reinterpret_cast<LPVOID>(address), size, oldProt, &tmp);
    return true;
}
