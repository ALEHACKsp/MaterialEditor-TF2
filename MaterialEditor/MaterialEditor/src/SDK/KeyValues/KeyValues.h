#pragma once

class CKeyValues
{
public:
	int m_iKeyName;
	char *m_sValue;
	wchar_t *m_wsValue;

	union
	{
		int m_iValue;
		float m_flValue;
		void *m_pValue;
		unsigned char m_Color[4];
	};

	char m_iDataType;
	char m_bHasEscapeSequences;
	char m_bEvaluateConditionals;
	char unused[1];

	CKeyValues *m_pPeer;
	CKeyValues *m_pSub;
	CKeyValues *m_pChain;

	bool LoadFromBuffer(char const *resource_name, const char *buffer, void *file_system = 0, const char *path_id = 0);
	void Initialize(char *name);
};