#pragma once
#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace EndScene
	{
		inline CHook Hook;
		using fn = HRESULT(__stdcall *)(IDirect3DDevice9 *);
		HRESULT __stdcall Func(IDirect3DDevice9 *pDevice);
		void Init();
	}
}