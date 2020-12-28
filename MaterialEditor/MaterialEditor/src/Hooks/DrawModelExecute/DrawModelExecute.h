#pragma once
#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace DrawModelExecute
	{
		inline CHook Hook;
		using fn = void(__thiscall *)(IVModelRender *, const DrawModelState_t &, const ModelRenderInfo_t &, matrix3x4 *);
		void __stdcall Func(const DrawModelState_t &pState, const ModelRenderInfo_t &pInfo, matrix3x4 *pBoneToWorld);
		void Init();
	}
}