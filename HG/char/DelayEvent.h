// DelayEvent.h: interface for the CDelayEvent class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELAYEVENT_H__047EB960_D8C0_11D2_B145_00001C7030A6__INCLUDED_)
#define AFX_DELAYEVENT_H__047EB960_D8C0_11D2_B145_00001C7030A6__INCLUDED_

#include <windows.h>

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#define DELAYEVENTTYPE_DAMAGEOBJECT				1
#define DELAYEVENTTYPE_MAGICRELEASE				2
#define DELAYEVENTTYPE_USEITEM_SKILL			3
#define DELAYEVENTTYPE_METEORSTRIKE				4
#define DELAYEVENTTYPE_DOMETEORSTRIKEDAMAGE		5
#define DELAYEVENTTYPE_CALCMETEORSTRIKEEFFECT	6
#define DELAYEVENTTYPE_ANCIENT_TABLET			7

#define DELAYEVENTTYPE_END_APOCALYPSE			8
#define DELAYEVENTTYPE_KILL_ABADDON				9
class CDelayEvent  
{										  
public:

	CDelayEvent();
	virtual ~CDelayEvent();

	int m_iDelayType;
	int m_iEffectType;

	char m_cMapIndex;
	int m_dX, m_dY;

	int  m_iTargetH;
	char m_cTargetType;
	int m_iV1, m_iV2, m_iV3;

	DWORD m_dwTriggerTime;
};

#endif // !defined(AFX_DELAYEVENT_H__047EB960_D8C0_11D2_B145_00001C7030A6__INCLUDED_)
