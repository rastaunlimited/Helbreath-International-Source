#if !defined(AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include "..\defs.hpp"

class CMsg
{
public:
	void Get(char * Data, DWORD * pSize, int * pIndex, char * pKey);
	BOOL bPut(char * Data, DWORD dwSize, int iIndex, char cKey);
	CMsg();
	virtual ~CMsg();

	char * m_Data;
	DWORD  m_dwSize;

	int    m_iIndex;
	char   m_cKey;   
};

#endif // !defined(AFX_MSG_H__57BA71C0_B929_11D2_B143_00001C7030A6__INCLUDED_)
