#include <Windows.h>
#include <d3dcommon.h>
#include <d3dcompiler.h>

HMODULE hOriginalDll = nullptr;

extern "C" {
    FARPROC fpD3DCompile = nullptr;
    FARPROC fpD3DReflect = nullptr;
    FARPROC fpD3DPreprocess = nullptr;
    FARPROC fpD3DGetBlobPart = nullptr;
    FARPROC fpD3DDisassemble = nullptr;
}

extern "C" BOOL LoadOriginalD3DCompiler()
{
    if (hOriginalDll)
        return TRUE;

    char path[MAX_PATH];
    GetSystemDirectoryA(path, MAX_PATH);
    strcat_s(path, "\\d3dcompiler_43.dll");

    hOriginalDll = LoadLibraryA(path);
    if (!hOriginalDll)
        return FALSE;

    fpD3DCompile = GetProcAddress(hOriginalDll, "D3DCompile");
    fpD3DReflect = GetProcAddress(hOriginalDll, "D3DReflect");
    fpD3DPreprocess = GetProcAddress(hOriginalDll, "D3DPreprocess");
    fpD3DGetBlobPart = GetProcAddress(hOriginalDll, "D3DGetBlobPart");
    fpD3DDisassemble = GetProcAddress(hOriginalDll, "D3DDisassemble");

    return TRUE;
}

extern "C" void FreeOriginalD3DCompiler()
{
    if (hOriginalDll)
    {
        FreeLibrary(hOriginalDll);
        hOriginalDll = nullptr;
    }
}

extern "C" HRESULT WINAPI D3DCompile(
    LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName,
    const D3D_SHADER_MACRO* pDefines, ID3DInclude* pInclude,
    LPCSTR pEntrypoint, LPCSTR pTarget, UINT Flags1, UINT Flags2,
    ID3DBlob** ppCode, ID3DBlob** ppErrorMsgs)
{
    if (!fpD3DCompile)
        LoadOriginalD3DCompiler();
    auto fn = reinterpret_cast<decltype(&D3DCompile)>(fpD3DCompile);
    return fn ? fn(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
        pEntrypoint, pTarget, Flags1, Flags2, ppCode, ppErrorMsgs)
        : E_FAIL;
}

extern "C" HRESULT WINAPI D3DReflect(
    LPCVOID pSrcData, SIZE_T SrcDataSize, REFIID pInterface, void** ppReflector)
{
    if (!fpD3DReflect)
        LoadOriginalD3DCompiler();
    auto fn = reinterpret_cast<decltype(&D3DReflect)>(fpD3DReflect);
    return fn ? fn(pSrcData, SrcDataSize, pInterface, ppReflector) : E_FAIL;
}

extern "C" HRESULT WINAPI D3DPreprocess(
    LPCVOID pSrcData, SIZE_T SrcDataSize, LPCSTR pSourceName,
    const D3D_SHADER_MACRO* pDefines, ID3DInclude* pInclude,
    ID3DBlob** ppCodeText, ID3DBlob** ppErrorMsgs)
{
    if (!fpD3DPreprocess)
        LoadOriginalD3DCompiler();
    auto fn = reinterpret_cast<decltype(&D3DPreprocess)>(fpD3DPreprocess);
    return fn ? fn(pSrcData, SrcDataSize, pSourceName, pDefines, pInclude,
        ppCodeText, ppErrorMsgs)
        : E_FAIL;
}

extern "C" HRESULT WINAPI D3DGetBlobPart(
    LPCVOID pSrcData, SIZE_T SrcDataSize, D3D_BLOB_PART Part,
    UINT Flags, ID3DBlob** ppPart)
{
    if (!fpD3DGetBlobPart)
        LoadOriginalD3DCompiler();
    auto fn = reinterpret_cast<decltype(&D3DGetBlobPart)>(fpD3DGetBlobPart);
    return fn ? fn(pSrcData, SrcDataSize, Part, Flags, ppPart) : E_FAIL;
}

extern "C" HRESULT WINAPI D3DDisassemble(
    LPCVOID pSrcData, SIZE_T SrcDataSize, UINT Flags,
    LPCSTR szComments, ID3DBlob** ppDisassembly)
{
    if (!fpD3DDisassemble)
        LoadOriginalD3DCompiler();
    auto fn = reinterpret_cast<decltype(&D3DDisassemble)>(fpD3DDisassemble);
    return fn ? fn(pSrcData, SrcDataSize, Flags, szComments, ppDisassembly)
        : E_FAIL;
}
