// Magic.h: interface for the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAGIC_H__CD611900_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_)
#define AFX_MAGIC_H__CD611900_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>

#define MAXMAGICEFFECTS			35

enum magicValuesIndices{
	MAGICV_TYPE =				0,
	MAGICV_THROW =				0,
	MAGICV_RANGE =				1,
	MAGICV_POISONLVL =			1,
	MAGICV_BONUS =				2,
	MAGICV_LINEARTHROW =		3,
	MAGICV_LINEARRANGE =		4,
	MAGICV_LINEARBONUS =		5,
	MAGICV_ICEDURATION =		6,
	MAGICV_ARMORDEC =			6,
	MAGICV_DYNAMICOBJ =			6,
	MAGICV_DYNAMICTYPE =		7
};

enum magicTypes{
	MAGICTYPE_NONE,
	MAGICTYPE_DAMAGE_SPOT,
	MAGICTYPE_HPUP_SPOT,
	MAGICTYPE_DAMAGE_AREA,
	MAGICTYPE_SPDOWN_SPOT,	// unused
	MAGICTYPE_SPDOWN_AREA,
	MAGICTYPE_SPUP_SPOT,		// unused
	MAGICTYPE_SPUP_AREA,
	MAGICTYPE_TELEPORT,
	MAGICTYPE_SUMMON,
	MAGICTYPE_CREATE,
	MAGICTYPE_PROTECT,
	MAGICTYPE_HOLDOBJECT,
	MAGICTYPE_INVISIBILITY,
	MAGICTYPE_CREATE_DYNAMIC,
	MAGICTYPE_POSSESSION,
	MAGICTYPE_CONFUSE,
	MAGICTYPE_POISON,
	MAGICTYPE_BERSERK,
	MAGICTYPE_DAMAGE_LINEAR,
	MAGICTYPE_POLYMORPH,
	MAGICTYPE_DAMAGE_AREA_NOSPOT,
	MAGICTYPE_TREMOR,
	MAGICTYPE_ICE,
	MAGICTYPE_DAMAGE_SPOT_SPDOWN,		// no spells
	MAGICTYPE_DAMAGE_AREA_NOSPOT_SPDOWN,

	MAGICTYPE_DAMAGE_AREA_ARMOR_BREAK,
	MAGICTYPE_ICE_LINEAR,

	MAGICTYPE_CANCELLATION,
	MAGICTYPE_INHIBITION,	
	MAGICTYPE_DAMAGE_LINEAR_SPDOWN,
	MAGICTYPE_SCAN,
	MAGICTYPE_RESURRECTION,
	MAGICTYPE_DAMAGE_AREA_MOVE
};

enum magicNum{
	MAGIC_INVISIBILITY =		32,
	MAGIC_ICESTORM =			55
};

enum magicChldProtect{
	MAGICPROTECT_PFA =		1,
	MAGICPROTECT_PFM =		2,
	MAGICPROTECT_AMP =		5,
	MAGICPROTECT_DS =		3,
	MAGICPROTECT_GDS =		4
};

#include "unit.h"

class CMagic  
{									 
public:
	CMagic();
	virtual ~CMagic();

	char m_cName[31];

	short m_sType;
	DWORD m_dwDelayTime, m_dwLastTime;
	short m_manaCost;
	char m_hRange, m_vRange;
	short m_sValue[8];
	short m_sIntLimit;
	int   m_iGoldCost;

	char  m_cCategory; 	int   m_iAttribute; 

	void Effect_RecSP(Unit * caster, Unit * target, uint32 dthrow, uint32 droll, uint32 dbonus);
};

#endif // !defined(AFX_MAGIC_H__CD611900_EF3A_11D2_9B6C_00001C7030A6__INCLUDED_)
