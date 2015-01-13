#ifndef DROPMANAGER_H
#define DROPMANAGER_H
#pragma once

#include "..\shared\npcType.h"
#include "..\shared\items.h"
#include "math.h"

#define MAXNPCDROPTIERS		3
#define MAXNPCDROPS			40

#define ONNPCDEATH			0
#define ONNPCDELETE			1

class CNpc;

struct TierDrop
{
	long prob;
	long itemID;

	void SetDrop(long itemid, long probability)
	{
		itemID = itemid;
		prob = probability;
	}
};

struct Tier
{
	long prob;
	long dropsNum;
	long dropProbSum;
	TierDrop drops[MAXNPCDROPS];

	bool AddDrop(long itemid, long probability)
	{
		if(dropsNum >= MAXNPCDROPS)
			return FALSE;
		dropProbSum += probability;
		drops[dropsNum].SetDrop(itemid, probability);
		++dropsNum;
		return TRUE;
	}
};

struct NpcDrop
{
	long tiersNum;
	long tierProbSum;
	Tier tiers[MAXNPCDROPTIERS];
	uint32 secDropNum;

	Tier * AddTier(long probability)
	{
		if(tiersNum >= MAXNPCDROPTIERS)
			return NULL;
		tierProbSum += probability;
		tiers[tiersNum].prob = probability;
		++tiersNum;
		return &tiers[tiersNum-1];
	}
};

class DropManager
{
public:
	DropManager();
	~DropManager();
	void InitDrops();

	long Roll(const CNpc * npc, const long dropType = ONNPCDEATH) const;
	bool HasPrimaryDrop(NpcID id) const;
	bool HasPrimaryDrop(const CNpc * id) const;
	bool HasSecondaryDrop(NpcID id) const;
	bool HasSecondaryDrop(const CNpc * id) const;
	uint32 GetSecDropNum(NpcID npcType)	const { return _npcDeleteDrops[npcType].secDropNum; };

protected:
	void _ParseXML();

	uint32 _dropCount;
	NpcDrop _npcDrops[MAXNPCTYPES];
	NpcDrop _npcDeleteDrops[MAXNPCTYPES];
};

#endif