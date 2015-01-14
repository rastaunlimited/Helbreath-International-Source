// StrTok.cpp: implementation of the CStrTok class.
//
//////////////////////////////////////////////////////////////////////

#include "StrTok.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CStrTok::CStrTok(char * Data, char * pSeps)
{
	m_Data = Data;
	m_pSeps = pSeps;

	m_iDataLength = strlen(Data);
	m_iCurLoc     = 0;
}

CStrTok::~CStrTok()
{

}

char * CStrTok::pGet()
{
 register int i = 0;
 char cNextData;
 BOOL bFlag;

	ZeroMemory(m_cToken, sizeof(m_cToken));

	while (m_iCurLoc < m_iDataLength) {

		if (m_iCurLoc <= (m_iDataLength - 2))
			 cNextData = m_Data[m_iCurLoc+1];
		else cNextData = NULL;

		if (_bIsSeperator(m_Data[m_iCurLoc], cNextData))
		{	bFlag = FALSE;
			while (bFlag == FALSE) {
				if (m_iCurLoc <= (m_iDataLength - 2))
					 cNextData = m_Data[m_iCurLoc+1];
				else cNextData = NULL;
				if (_bIsSeperator(m_Data[m_iCurLoc], cNextData)) {
					m_iCurLoc++;	
				}
				else bFlag = TRUE;

				if (m_iCurLoc >= (m_iDataLength-1)) bFlag = TRUE;
			}
			
			return (char *)(&m_cToken);
		}
		else {
			// separator
			m_cToken[i] = m_Data[m_iCurLoc];
			i++;
			m_iCurLoc++;
		}
	}

	if (strlen(m_cToken) != 0) return (char *)(&m_cToken);
	return NULL;
}

bool CStrTok::_bIsSeperator(char Data, char cNextData)
{
 int i = 0;
	
	if (Data == NULL) return TRUE;
	if ((Data == 0x0D) && (cNextData == 0x0A)) return TRUE;
	
	while (m_pSeps[i] != NULL) {
		if (m_pSeps[i] == Data) return TRUE;
		i++;
	}
	return FALSE;
}

