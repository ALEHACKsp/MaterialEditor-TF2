#pragma once
#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace Reset
	{
		inline CHook Hook;
		using fn = HRESULT(__stdcall *)(IDirect3DDevice9 *, D3DPRESENT_PARAMETERS *);
		HRESULT __stdcall Func(IDirect3DDevice9 *pDevice, D3DPRESENT_PARAMETERS *pPresentParams);
		void Init();
	}
}