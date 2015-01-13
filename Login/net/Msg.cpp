#include "Msg.h"
//=============================================================================
CMsg::CMsg()
{
	m_pData  = NULL;
	m_dwSize = NULL;
}
//=============================================================================
CMsg::~CMsg()						   
{
	if (m_pData != NULL) delete m_pData;
}
//=============================================================================
BOOL CMsg::bPut(char * pData, DWORD dwSize, int iIndex, char cKey)
{
	m_pData = new char [dwSize + 1];
	if (m_pData == NULL) return FALSE;
	ZeroMemory(m_pData, dwSize + 1);
	memcpy(m_pData, pData, dwSize);
	
	m_dwSize = dwSize;
	m_iIndex = iIndex;
	m_cKey   = cKey;

	return TRUE;
}
//=============================================================================
void CMsg::Get(char * pData, DWORD * pSize, int * pIndex, char * pKey)
{
	memcpy(pData, m_pData, m_dwSize);
	*pSize  = m_dwSize;
	*pIndex = m_iIndex;
	*pKey   = m_cKey;
}
//=============================================================================