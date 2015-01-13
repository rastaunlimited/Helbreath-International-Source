#include <windows.h>
#include "..\HG.h"
#include "Unit.h"

extern class CGame *   g_game;
extern class CMagic ** g_magicConfigList;
extern class CClient ** g_clientList;

Unit::Unit(void)
{
	m_bIsKilled   = FALSE;
	m_killerh = -1;
	m_sOriginalType      = NULL;
	m_iStatus    = NULL;
}

Unit::~Unit(void)
{
}

void Unit::SetStatusFlag(long flag, bool enabled)
{
	if (enabled) 
		m_iStatus |= flag;
	else 
		m_iStatus &= STATUS_ALL - flag;

	g_game->SendEventToNearClient_TypeA(m_handle, m_ownerType, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);
}

void Unit::ToggleStatusFlag(long flag)
{
	m_iStatus ^= flag;	
	
	g_game->SendEventToNearClient_TypeA(m_handle, m_ownerType, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);
}

bool Unit::GetStatusFlag(long flag) const
{
	return (m_iStatus & flag) ? TRUE : FALSE;
}

void Unit::SetMagicFlag(short magicType, bool enabled)
{
	long flag = NULL;

	switch(magicType)
	{
		case MAGICTYPE_INVISIBILITY:
			flag = STATUS_INVISIBILITY;
			break;
		case MAGICTYPE_ICE:
		case MAGICTYPE_ICE_LINEAR:
			flag = STATUS_FROZEN;
			break;
		case MAGICTYPE_BERSERK:
			flag = STATUS_BERSERK;
			break;
		case MAGICTYPE_PROTECT:
			switch(m_cMagicEffectStatus[magicType])
			{
			case MAGICPROTECT_PFA:
				flag = STATUS_PFA;
				break;
			case MAGICPROTECT_PFM:
			case MAGICPROTECT_AMP:
				flag = STATUS_PFM;
				break;
			case MAGICPROTECT_DS:
			case MAGICPROTECT_GDS:
				flag = STATUS_DEFENSESHIELD;
				break;
			}
			break;
		case MAGICTYPE_CONFUSE:
			switch (m_cMagicEffectStatus[magicType])
			{
			case 1:	// Language confuse
				break;
			case 2:	// Confusion
				break;
			case 3:
				flag = STATUS_ILLUSION;
				break;
			case 4:	
				flag = STATUS_ILLUSIONMOVEMENT;
				break;
			}
			break;
		default:
			// No flag
			return;
	}

	SetStatusFlag(flag, enabled);
}

bool Unit::AddMagicEffect(short magicType, long effectTime, char kind)
{
	//char magicType = spell->m_sType;
	DWORD  dwTime = timeGetTime();

	if(m_cMagicEffectStatus[magicType])
		return FALSE;

	m_cMagicEffectStatus[magicType] = kind;
	g_game->RegisterDelayEvent(DELAYEVENTTYPE_MAGICRELEASE, magicType, dwTime + (effectTime)_s, 
		this, NULL, NULL, NULL, kind, NULL, NULL);

	if (IsPlayer())
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_MAGICEFFECTON, magicType, kind, NULL, NULL);

	SetMagicFlag(magicType, TRUE);
	return TRUE;
}

bool Unit::RemoveMagicEffect(char magicType)
{
	if(!m_cMagicEffectStatus[magicType])
		return FALSE;

	if (IsPlayer())
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_MAGICEFFECTOFF, magicType, m_cMagicEffectStatus[magicType], NULL, NULL);

	SetMagicFlag(magicType, FALSE);
	m_cMagicEffectStatus[magicType] = NULL;
	g_game->RemoveFromDelayEventList(this, magicType);
	return TRUE;
}

void Unit::SetSideFlag(Side side)
{
	SetNibble(m_iStatus, 7, side);
}

CClient * Unit::GetKiller() const
{
	if(m_killerh != -1)
		return g_clientList[ m_killerh ];
	else
		return NULL;
}