#include "hg.h"

extern class CGame *   g_game;
extern class CMap	**	g_mapList;

CAstoria::CAstoria(const EventType type) : _eventType(type)
{
	for(int i=0; i < MAXSIDES; i++)
	{
		_sideStats[i].deaths = 0;
		_sideStats[i].kills = 0;
	}

	_relic = NULL;
	_relicHolder = NULL;
	_relicOwnedSide = NEUTRAL;
	_relicOwnedTime = 0;
	m_relicHolderSteps = 0;

	_shieldCount = MAXALTARS;

	g_game->ShuffleAstoriaBasePos();

	switch(_eventType)
	{
	case ET_CAPTURE:
		_CaptureStart();
		break;
	}

	g_game->CreateAstoriaFlags();

	m_beginTime = timeGetTime();
}

CAstoria::~CAstoria(void)
{
	switch(_eventType)
	{
	case ET_CAPTURE:
		_CaptureEnd();
		break;
	}

	g_game->DeleteFlags();
}

void CAstoria::PlayerGetRelic(CClient * player)
{ 
	_relicHolder = player;
	_relicHolder->SetStatusFlag(STATUS_RELICHOLDER, TRUE);
	_relicHolder->RemoveMagicEffect(MAGICTYPE_INVISIBILITY);

	g_game->NotifyRelicGrabbed(_relicHolder);
}

void CAstoria::PlayerDropRelic(CClient * player)
{ 
	player->SetStatusFlag(STATUS_RELICHOLDER, FALSE);
	_relicHolder = NULL;

	_relicPos.x = player->m_sX;
	_relicPos.y = player->m_sY;

	m_relicHolderSteps = 0;

	if(_IsRelicInAltar())
	{
		_relicOwnedTime = timeGetTime();
		g_game->NotifyRelicInAltar(_relicOwnedSide);
	}
}

bool CAstoria::CheckVictory()
{
	switch(_eventType)
	{
	case ET_CAPTURE:
		if(_IsRelicInAltar() && timeGetTime() - _relicOwnedTime > RELICVICTORYTIME)
		{
			return TRUE;
		}
		break;
	case ET_DESTROY_SHIELD:
		break;
	}
	return FALSE;
}

Side CAstoria::GetVictoriousSide() const
{
	switch(_eventType)
	{
	case ET_CAPTURE:
		return _relicOwnedSide;
	case ET_DESTROY_SHIELD:
		break;
	}
	return NEUTRAL;
}

bool CAstoria::_IsRelicInAltar()
{
	if(_relicHolder) return FALSE;

	for(int i = 0; i < MAXALTARS; i++)
	{
		if(_relicPos == altarPos[i])
		{
			_relicOwnedSide = g_game->m_astoriaBasePos[i];
			return TRUE;
		}
	}
	return FALSE;
}

void CAstoria::_CaptureStart()
{
	_relic = new CItem(); 
	g_game->_bInitItemAttr(_relic, ITEM_RELIC);
	_relicPos = relicStartPos;

	g_mapList[g_game->m_iAstoriaMapIndex]->bSetItem(_relicPos.x, _relicPos.y, _relic);
	g_game->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, COMMONTYPE_SETITEM, g_game->m_iAstoriaMapIndex,
		_relicPos.x, _relicPos.y, _relic->m_sSprite, _relic->m_sSpriteFrame, _relic->m_cItemColor);
}

void CAstoria::_CaptureEnd()
{
	if(_relicHolder)
	{
		uint32 i = _relicHolder->HasItem(ITEM_RELIC);
		if(i != ITEM_NONE)
			g_game->DropItemHandler(_relicHolder->m_handle, i, 1, _relicHolder->m_pItemList[i]->m_cName, FALSE);
	}

	short nextItemSprite, nextItemSpriteFrame;
	char  nextItemColor;

	g_mapList[g_game->m_iAstoriaMapIndex]->pGetItem(_relicPos.x, _relicPos.y, &nextItemSprite, &nextItemSpriteFrame, &nextItemColor);

	g_game->SendEventToNearClient_TypeB(MSGID_EVENT_COMMON, COMMONTYPE_SETITEM, g_game->m_iAstoriaMapIndex,
		_relicPos.x, _relicPos.y, nextItemSprite, nextItemSpriteFrame, nextItemColor);

	if(_relic)
		delete _relic;
}

bool CAstoria::ShieldDestroyed()
{
	_shieldCount--;

	return (_shieldCount == 1) ? TRUE : FALSE;
}

void CAstoria::PlayerKill(CClient * killer, CClient * victim)
{
	if(killer->m_side != victim->m_side)
		_sideStats[killer->m_side].kills++;
	_sideStats[victim->m_side].deaths++;

	g_game->NotifyEventStats(_sideStats);
}