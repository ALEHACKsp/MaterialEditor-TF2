#include "Pattern.h"

#define INRANGE(x,a,b)    ((x) >= (a) && (x) <= (b))
#define GetBits( x )    (INRANGE(((x)&(~0x20)),'A','F') ? (((x)&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? (x) - '0' : 0))
#define GetByte( x )    (GetBits((x)[0]) << 4 | GetBits((x)[1]))

DWORD CPattern::FindPattern(DWORD dwAddress, DWORD dwLength, LPCWSTR szPattern)
{
	const wchar_t *pat = szPattern;
	DWORD firstMatch = NULL;

	for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
	{
		if (!*pat)
			return firstMatch;

		if (*(PBYTE)pat == '\?' || *(BYTE *)pCur == GetByte(pat))
		{
			if (!firstMatch)
				firstMatch = pCur;

			if (!pat[2])
				return firstMatch;

			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?')
				pat += 3;

			else pat += 2;
		}

		else
		{
			pat = szPattern;
			firstMatch = 0;
		}
	}

	return NULL;
}

HMODULE CPattern::GetModuleHandleSafe(LPCWSTR szModuleName)
{
	HMODULE hmModuleHandle = nullptr;

	do {
		hmModuleHandle = GetModuleHandleW(szModuleName);
		Sleep(1);
	} while (hmModuleHandle == nullptr);

	return hmModuleHandle;
}

DWORD CPattern::Find(LPCWSTR szModuleName, LPCWSTR szPattern)
{
	HMODULE hmModule = GetModuleHandleSafe(szModuleName);
	static PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
	static PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);
	return FindPattern(((DWORD)hmModule) + pNTHeaders->OptionalHeader.BaseOfCode, ((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode, szPattern);
}