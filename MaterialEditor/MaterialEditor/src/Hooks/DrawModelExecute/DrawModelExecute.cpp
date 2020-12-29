#include "DrawModelExecute.h"
#include "../../Editor/Editor.h"

void __stdcall Hooks::DrawModelExecute::Func(const DrawModelState_t &pState, const ModelRenderInfo_t &pInfo, matrix3x4 *pBoneToWorld)
{
	if (const auto &pMaterial = g_Editor.GetLoadedMaterial())
	{
		if (pInfo.entity_index > 0 && pInfo.entity_index < 32)
		{
			g_pModelRender->ForcedMaterialOverride(pMaterial);
			Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);
			g_pModelRender->ForcedMaterialOverride(nullptr);
			return;
		}
	}

	Hook.CallOriginal<fn>()(g_pModelRender, pState, pInfo, pBoneToWorld);
}

void Hooks::DrawModelExecute::Init()
{
	fn FN = reinterpret_cast<fn>(Utils::GetVFuncPtr(g_pModelRender, 19));
	Hook.Create(reinterpret_cast<void *>(FN), reinterpret_cast<void *>(Func));
}