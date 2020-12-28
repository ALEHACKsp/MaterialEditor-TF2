#pragma once
#include "Hook/Hook.h"
#include "Pattern/Pattern.h"
#include "Vector/Vector.h"
#include "Interface/Interface.h"
#include "Color/Color.h"

namespace Utils
{
	inline uintptr_t GetVFuncPtr(void *pBaseClass, unsigned int nIndex)
	{
		return static_cast<uintptr_t>((*static_cast<int **>(pBaseClass))[nIndex]);
	}
}