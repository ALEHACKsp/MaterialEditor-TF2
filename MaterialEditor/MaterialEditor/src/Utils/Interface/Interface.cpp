#include "Interface.h"

PVOID CInterface::Get(LPCWSTR szModule, PCCH szObject)
{
	if (const auto Module = GetModuleHandleW(szModule))
	{
		const auto dwCreateInterface = reinterpret_cast<DWORD>(GetProcAddress(Module, "CreateInterface"));
		const auto dwShortJmp = dwCreateInterface + 0x5;
		const auto dwJmp = (dwShortJmp + *reinterpret_cast<DWORD *>(dwShortJmp)) + 0x4;

		auto pList = **reinterpret_cast<Interface_t ***>(dwJmp + 0x6);

		while (pList)
		{
			if ((strstr(pList->szInterfaceName, szObject) && (strlen(pList->szInterfaceName) - strlen(szObject)) < 5))
				return pList->Interface();

			pList = pList->NextInterface;
		}
	}

	return nullptr;
}