#pragma once
#include <Windows.h>

class CInterface
{
private:
	typedef PVOID(*InstantiateInterface)();

	struct Interface_t
	{
		InstantiateInterface Interface;
		PCHAR szInterfaceName;
		Interface_t *NextInterface;
	};

public:
	PVOID Get(LPCWSTR szModule, PCCH szObject);
};

inline CInterface g_Interface;