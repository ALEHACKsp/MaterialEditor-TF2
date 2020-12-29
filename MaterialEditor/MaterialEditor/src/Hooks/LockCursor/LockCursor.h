#pragma once
#include "../../SDK/SDK.h"

namespace Hooks
{
	namespace LockCursor
	{
		inline CHook Hook;
		using fn = void(__thiscall *)(ISurface *);
		void __stdcall Func();
		void Init();
	}
}