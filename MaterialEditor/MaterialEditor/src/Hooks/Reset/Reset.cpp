#include "Reset.h"
#include "../../Editor/Editor.h"

HRESULT __stdcall Hooks::Reset::Func(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentParams)
{
    ImGui_ImplDX9_InvalidateDeviceObjects();
    HRESULT Original = Hook.CallOriginal<fn>()(pDevice, pPresentParams);
    ImGui_ImplDX9_CreateDeviceObjects();
    return Original;
}

void Hooks::Reset::Init()
{
    fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(reinterpret_cast<void **>(g_dwDirectXDevice), 16));
    Hook.Create(reinterpret_cast<void *>(FN), reinterpret_cast<void *>(Func));
}