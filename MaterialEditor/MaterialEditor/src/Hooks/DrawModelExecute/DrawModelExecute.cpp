#include "DrawModelExecute.h"

void __stdcall Hooks::DrawModelExecute::Func(const DrawModelState_t &pState, const ModelRenderInfo_t &pInfo, matrix3x4 *pBoneToWorld)
{
	Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);
}

void Hooks::DrawModelExecute::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(g_pModelRender, 19));
	Hook.Create(reinterpret_cast<void *>(FN), reinterpret_cast<void *>(Func));
}