#include "hg.h"

#include "droplist.hxx"

extern class CGame *   g_game;

DropManager::DropManager(void)
{
	_dropCount = 0;

	for(int npc=0; npc < MAXNPCTYPES; npc++)
	{
		for(int tier=0; tier < MAXNPCDROPTIERS; tier++)
		{
			_npcDrops[npc].tiersNum = 0;
			_npcDrops[npc].tierProbSum = 0;
			_npcDrops[npc].tiers[tier].prob = 0;
			_npcDrops[npc].tiers[tier].dropsNum = 0;
			_npcDrops[npc].tiers[tier].dropProbSum = 0;;
			for(int drop=0; drop < MAXNPCDROPS; drop++)
			{
				_npcDrops[npc].tiers[tier].drops[drop].SetDrop(0,0);
			}


			_npcDeleteDrops[npc].tiersNum = 0;
			_npcDeleteDrops[npc].tierProbSum = 0;
			_npcDeleteDrops[npc].tiers[tier].prob = 0;
			_npcDeleteDrops[npc].tiers[tier].dropsNum = 0;
			_npcDeleteDrops[npc].tiers[tier].dropProbSum = 0;
			for(int drop=0; drop < MAXNPCDROPS; drop++)
			{
				_npcDeleteDrops[npc].tiers[tier].drops[drop].SetDrop(0,0);
			}
		}
	}
}

DropManager::~DropManager(void)
{
}

void DropManager::InitDrops(void)
{
	try
	{
		_ParseXML();
	}
	catch (const xml_schema::exception& e)
	{
		string exc = "XML ERROR: ";
		exc += e.what();
		LogError(exc);
		return;
	}

	sstream err;
	err << "Total drop items: " << _dropCount;
	PutLogList(err.str());
}

void DropManager::_ParseXML()
{
	std::auto_ptr<droplist_t> dl (droplist ("..\\configs\\droplist.xml"));

	for (droplist_t::npc_t_const_iterator npc (dl->npc_t().begin ());
		npc != dl->npc_t().end ();
		++npc)
	{
		string npcName;
		npcName = npc->name();
		uint32 npcType = g_game->FindNPC(npcName);
		if(npcType == NPC_INVALID)	
		{
			sstream err;
			err << "Unknown NPC in Droplist: "<< npcName;
			LogError(err.str());
			continue;
		}
		else if(HasPrimaryDrop(npcType) || HasSecondaryDrop(npcType))
		{
			sstream err;
			err << "Duplicated NPC in Droplist: "<< npcName;
			LogError(err.str());
			continue;
		}

		for (npc_t::tier_t_const_iterator t (npc->tier_t().begin ());
			t != npc->tier_t().end ();
			++t)
		{
			Tier * tier;
			NpcDrop * drop;

			if(t->type() == "primary")
			{
				drop = &_npcDrops[npcType];
				tier = drop->AddTier(t->prob());
			}
			else
			{
				drop = &_npcDeleteDrops[npcType];
				tier = _npcDeleteDrops[npcType].AddTier(t->prob());
			}

			drop->secDropNum = npc->num();

			if(!tier)
			{
				sstream err;
				err << "Too many a Tier in NPC("<< npcName <<')';
				LogError(err.str());	
				continue;
			}

			for (tier_t::item_t_const_iterator item (t->item_t().begin ());
				item != t->item_t().end ();
				++item)
			{
				string itemName = item->name();

				uint32 itemID;
				if(itemName == "nothing")
					itemID = ITEM_NONE;
				else
					itemID = g_game->FindItem(itemName);

				if(itemID == ITEM_INVALID)	
				{
					sstream err;
					err << "Unknown item("<< itemName <<") in NPC("<< npcName << ')';
					LogError(err.str());
					continue;
				}

				if(! tier->AddDrop( itemID, item->prob()) )
				{
					sstream err;
					err << "Too many a Drop("<< itemName <<") in NPC("<< npcName <<')';
					LogError(err.str());	
					continue;
				}

				_dropCount++;
			}
		}
	}
}

long DropManager::Roll(const CNpc * npc, long dropType) const
{
	const NpcDrop * drop;
	const Tier * tier = 0;
	float factor = 1.0f;

	switch(dropType)
	{
	case ONNPCDEATH:
		drop = &_npcDrops[npc->m_sType];
		break;
	case ONNPCDELETE:
		drop = &_npcDeleteDrops[npc->m_sType];
		if(CClient * killer = npc->GetKiller())
			factor = killer->GetDropFactor();

		if(g_game->m_iMiddlelandMapIndex != -1 && g_game->m_iMiddlelandMapIndex == npc->m_cMapIndex)
		{
			factor *= 0.9f;
		}

		break;
	default:
		return ITEM_NONE;
	}


	long tierRoll = dice(1, drop->tierProbSum);
	for(int n=0; n < drop->tiersNum; n++)
	{
		if(tierRoll <= drop->tiers[n].prob){
			tier = &drop->tiers[n];
			break;
		}
		tierRoll -= drop->tiers[n].prob;
	}

	if(!tier || tier->dropsNum == 0) return ITEM_NONE;


	long firstDropProb = tier->drops[0].prob * factor;

	long dropRoll = dice(1, tier->dropProbSum - (tier->drops[0].prob - firstDropProb));

	if(dropRoll <= firstDropProb){
		return tier->drops[0].itemID;
	}
	dropRoll -= firstDropProb;

	for(int n=1; n < tier->dropsNum; n++)
	{
		if(dropRoll <= tier->drops[n].prob){
			return tier->drops[n].itemID;
		}
		dropRoll -= tier->drops[n].prob;
	}

	return ITEM_NONE;
}

bool DropManager::HasPrimaryDrop(NpcID npcType) const
{
	return (_npcDrops[npcType].tiersNum > 0) ? TRUE : FALSE;
}
bool DropManager::HasPrimaryDrop(const CNpc * npc) const
{
	return (_npcDrops[npc->m_sType].tiersNum > 0) ? TRUE : FALSE;
}

bool DropManager::HasSecondaryDrop(NpcID npcType) const
{
	return (_npcDeleteDrops[npcType].tiersNum > 0) ? TRUE : FALSE;
}
bool DropManager::HasSecondaryDrop(const CNpc * npc) const
{
	return (_npcDeleteDrops[npc->m_sType].tiersNum > 0) ? TRUE : FALSE;
}
