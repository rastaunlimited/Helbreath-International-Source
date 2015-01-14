#include "Msg.h"
//=============================================================================
CMsg::CMsg()
{
	m_Data  = NULL;
	m_dwSize = NULL;
}
//=============================================================================
CMsg::~CMsg()						   
{
	if (m_Data != NULL) delete m_Data;
}
//=============================================================================
BOOL CMsg::bPut(char * Data, DWORD dwSize, int iIndex, char cKey)
{
	m_Data = new char [dwSize + 1];
	if (m_Data == NULL) return FALSE;
	ZeroMemory(m_Data, dwSize + 1);
	memcpy(m_Data, Data, dwSize);
	
	m_dwSize = dwSize;
	m_iIndex = iIndex;
	m_cKey   = cKey;

	return TRUE;
}
//=============================================================================
void CMsg::Get(char * Data, DWORD * pSize, int * pIndex, char * pKey)
{
	memcpy(Data, m_Data, m_dwSize);
	*pSize  = m_dwSize;
	*pIndex = m_iIndex;
	*pKey   = m_cKey;
}
//=============================================================================