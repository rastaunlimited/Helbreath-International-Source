// Npc.h: interface for the CNpc class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_)
#define AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000


#include <windows.h>

#include "..\..\shared\npcType.h"
#include "Magic.h"

#define MAXWAYPOINTS			10

#define MOVETYPE_STOP			0
#define MOVETYPE_SEQWAYPOINT	1
#define MOVETYPE_RANDOMWAYPOINT	2
#define MOVETYPE_FOLLOW			3
#define MOVETYPE_RANDOMAREA		4
#define MOVETYPE_RANDOM			5
#define MOVETYPE_GUARD			6

#define BEHAVIOR_STOP			0
#define BEHAVIOR_MOVE			1
#define BEHAVIOR_ATTACK			2
#define BEHAVIOR_FLEE			3
#define BEHAVIOR_DEAD			4

#define ATTRIBUTE_EARTH			1
#define ATTRIBUTE_AIR			2
#define ATTRIBUTE_FIRE			3
#define ATTRIBUTE_WATER			4

class CNpc : public Unit
{
public:

	CNpc(char * pName5, int NpcH);
	virtual ~CNpc();
	bool initNpcAttr(char * pNpcName, char cSA);
	bool behavior_searchMaster();
	void behavior_move();
	void behavior_stop();
	void behavior_attack();
	bool behavior_manaCollector();
	void behavior_grandMagicGenerator();
	bool behavior_detector();
	void nextWaypointDest();
	void targetSearch(short * pTarget, char * pTargetType);
	int getDangerValue(short dX, short dY);
	void magicHandler(short dX, short dY, short sType);
	int GetGenLevel();

	char  m_cNpcName[21];

	char  m_cName[6];
	char  m_cMapIndex;
	short m_sX, m_sY;
	short m_dX, m_dY;
	short m_vX, m_vY;
	int   m_tmp_iError;
	RECT  m_rcRandomArea;

	char  m_cAction;
	char  m_cTurn;

	short m_sAppr2;

	DWORD m_dwTime;
	DWORD m_dwActionTime;
	DWORD m_dwHPupTime, m_dwMPupTime;
	DWORD m_dwDeadTime, m_dwRegenTime;

	int  m_iHitDice;
	int  m_iDefenseRatio;
	int  m_iHitRatio;
	int  m_iMagicHitRatio;
	int  m_iMinBravery;
	int  m_iExpDice;
	DWORD dwGoldDropValue;

	char m_cActionLimit;

	char m_cSize;
	char m_cAttackDiceThrow;
	char m_cAttackDiceRange;
	char m_cAttackBonus;
	char m_cBravery;
	char m_cResistMagic;
	char m_cMagicLevel;
	char m_cDayOfWeekLimit;		    
	char m_cChatMsgPresence;     
	int  m_iMaxMana;
																    
	char  m_cMoveType;
	char  m_cBehavior;
	short m_sBehaviorTurnCount;
	char  m_cTargetSearchRange;

	int   m_iFollowOwnerIndex;
	char  m_cFollowOwnerType;
	bool  m_bIsSummoned;            
	DWORD m_dwSummonedTime;
	int   m_iTargetIndex;
	char  m_cTargetType;
	char  m_cCurWaypoint;
	char  m_cTotalWaypoint;

	int   m_iSpotMobIndex;
	int   m_iWayPointIndex[MAXWAYPOINTS+1];

	bool  m_bIsPermAttackMode;		   
	int   m_iNoDieRemainExp;
	int   m_iAttackStrategy; 
	int   m_iAILevel;

	int   m_iAttackRange;
	/*
		AI-Level 
			1: 보통 행동 
			2: 에너지가 가장 낮은 목표물을 추적 
			3: 마법 보호중인 목표물 마법 공격대상에서 제외 
	*/
	int   m_iAttackCount;


	int   m_iLastDamage;
	int   m_iSummonControlMode;
	char  m_cAttribute;
	int   m_iAbsDamage;

	int   m_iItemRatio;
	int   m_iAssignedItem;
	char  m_cSpecialAbility;

									/*
case 0: break;
case 1:  "Penetrating Invisibility"
case 2:  "Breaking Magic Protection"
case 3:  "Absorbing Physical Damage"
case 4:  "Absorbing Magical Damage"
case 5:  "Poisonous"
case 6:  "Extremely Poisonous"
case 7:  "Explosive"
case 8:  "Hi-Explosive" 

									*/

	int	  m_iBuildCount;

	bool  m_bIsMaster;
	int   m_iV1;

	// 2002-09-17 #1
	int		m_iNpcitemType;

	int		m_iNpcitemMax;

	int		m_iNpcCrops;
	int		m_iCropsSkillLV;
};

#endif // !defined(AFX_NPC_H__6F7A5C80_A709_11D2_B143_00001C7030A6__INCLUDED_)
