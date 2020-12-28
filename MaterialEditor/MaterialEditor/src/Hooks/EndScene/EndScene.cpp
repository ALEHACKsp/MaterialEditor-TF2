#include "EndScene.h"
#include "../../Editor/Editor.h"

HRESULT __stdcall Hooks::EndScene::Func(IDirect3DDevice9 *pDevice)
{
	g_Editor.Render(pDevice);
	return Hook.CallOriginal<fn>()(pDevice);
}

void Hooks::EndScene::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(reinterpret_cast<void **>(g_dwDirectXDevice), 42));
	Hook.Create(reinterpret_cast<void *>(FN), reinterpret_cast<void *>(Func));
}