#ifndef UNIT_H
#define UNIT_H
#pragma once

#include "magic.h"

class CClient;

enum OwnerType{
	OWNERTYPE_NONE,
	OWNERTYPE_PLAYER,
	OWNERTYPE_NPC,
	OWNERTYPE_PLAYER_INDIRECT
};

class Unit abstract
{
public:
	Unit(void);
	virtual ~Unit(void);
	void SetStatusFlag(long flag, bool enabled);
	void ToggleStatusFlag(long flag);
	bool GetStatusFlag(long flag) const;
	void SetMagicFlag(short magicType, bool enabled);
	bool AddMagicEffect(short magicType, long effectTime, char kind = 1);
	bool RemoveMagicEffect(char magicType);
	void SetSideFlag(Side side);

	bool IsDead()		{ return (m_iHP > 0) ? FALSE : TRUE; }
	bool IsBerserked()	{ return m_cMagicEffectStatus[MAGICTYPE_BERSERK] ? TRUE : FALSE; }
	bool IsInvisible()	{ return m_cMagicEffectStatus[MAGICTYPE_INVISIBILITY] ? TRUE : FALSE; }

	bool IsPlayer()		{ return (m_ownerType == OWNERTYPE_PLAYER) ? TRUE : FALSE; }
	bool IsNPC()		{ return (m_ownerType == OWNERTYPE_NPC) ? TRUE : FALSE; }
	bool IsNeutral()	{ return (m_side == NEUTRAL) ? TRUE : FALSE; }
	bool IsAres()		{ return (m_side == ARESDEN) ? TRUE : FALSE; }
	bool IsElv()		{ return (m_side == ELVINE) ? TRUE : FALSE; }

	CClient * GetKiller() const;

	

	short m_handle;

	int  m_iHP;
	int  m_iMP;              
	int  m_iExp;
	uint8 m_side;
	uint32 m_iStatus;
	bool m_bIsKilled;
	long m_killerh;
	char  m_cMapIndex;

	char  m_cDir;
	short m_sType;
	short m_sOriginalType;
	short m_ownerType;

	char  m_cMagicEffectStatus[MAXMAGICEFFECTS];

	int   m_iGuildGUID;
};
#endif