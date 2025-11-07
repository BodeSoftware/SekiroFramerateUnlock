#pragma once
#include <Windows.h>
#include <string>

// INI file helper class
class IniConfig {
private:
    std::string iniPath;

    // Get the directory where the DLL is located
    static std::string GetDllDirectory() {
        char path[MAX_PATH];
        HMODULE hModule = nullptr;

        // Get handle to this DLL
        GetModuleHandleExA(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
            GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
            (LPCSTR)&GetDllDirectory, &hModule);

        if (GetModuleFileNameA(hModule, path, MAX_PATH) > 0) {
            std::string fullPath(path);
            size_t pos = fullPath.find_last_of("\\/");
            if (pos != std::string::npos) {
                return fullPath.substr(0, pos + 1);
            }
        }
        return "";
    }

public:
    IniConfig(const char* filename) {
        iniPath = GetDllDirectory() + filename;
    }

    // Read float value from INI
    float GetFloat(const char* section, const char* key, float defaultValue) {
        char buffer[256];
        GetPrivateProfileStringA(section, key, "", buffer, sizeof(buffer), iniPath.c_str());

        if (buffer[0] != '\0') {
            return static_cast<float>(atof(buffer));
        }
        return defaultValue;
    }

    // Check if INI file exists
    bool Exists() {
        DWORD attrs = GetFileAttributesA(iniPath.c_str());
        return (attrs != INVALID_FILE_ATTRIBUTES && !(attrs & FILE_ATTRIBUTE_DIRECTORY));
    }

    // Create default INI file if it doesn't exist
    void CreateDefault() {
        if (!Exists()) {
            WritePrivateProfileStringA("Settings", "TargetFPS", "144", iniPath.c_str());
        }
    }

    const std::string& GetPath() const { return iniPath; }
};