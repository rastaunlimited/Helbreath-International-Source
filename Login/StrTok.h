#if !defined(AFX_STRTOK_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_STRTOK_H__A9554BE2_A96B_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif

#include <windows.h>

class CStrTok  
{
public:
	char * pGet();
	CStrTok(char * Data, char * pSeps);
	virtual ~CStrTok();

	char * m_Data, * m_pSeps, m_cToken[1024];
	int    m_iDataLength, m_iCurLoc;

private:
	BOOL _bIsSeperator(char Data, char cNextData);
};

#endif
