#ifndef ASTORIA_H
#define ASTORIA_H
#pragma once

#include "..\\shared\\common.h"
#include "char\\client.h"

#define MAXALTARS	2

const Point relicStartPos = {168,207};
const Point altarPos[MAXALTARS] = {
	{28,105},
	//{38,321},
	{314,321}
};
const Point astoriaStartPos[MAXALTARS] = {
	{47,116},
	//{43,309},
	{302,302}
};

const Point astoriaFlagsPos[MAXALTARS][19] = {
	{
		{209,179},
		{210,179},

		{158,202},
		{164,198},
		{90,104},
		{88,111},
		{76,97},
		{74,110},
		{80,151},
		{88,144},
		{64,143},
		{81,135},
		{37,177},
		{42,144},
		{116,179},
		{125,172},

		{31,105},
		{25,105},
		{-1,-1}
	},
	/*{
		{210,179},

		{78,264},
		{85,269},
		{62,278},
		{72,286},
		{121,305},
		{128,317},
		{114,320},
		{112,310},
		{55,309},
		{49,311},
		{157,208},
		{166,217},
		{110,253},
		{102,245},

		{35,321},
		{41,321},
		{-1,-1}
	},*/
	{
		{211,179},
		{211,180},

		{272,270},
		{264,275},
		{270,286},
		{279,275},
		{245,306},
		{253,299},
		{264,312},
		{268,304},
		{293,297},
		{298,299},
		{175,215},
		{179,211},
		{232,256},
		{241,250},

		{311,321},
		{317,321},
		{-1,-1}
	}
};

class CAstoria
{
public:
	CAstoria(const EventType type);
	~CAstoria(void);

	bool IsCapture()					const { return (_eventType == ET_CAPTURE) ? TRUE : FALSE; }
	bool IsDestroyShield()			const { return (_eventType == ET_DESTROY_SHIELD) ? TRUE : FALSE; }
	EventType GetEventType()		const { return _eventType; }
	const Casualties * GetStats() const { return _sideStats; }
	bool CheckVictory();
	Side GetVictoriousSide() const;

	void PlayerKill(CClient * killer, CClient * victim);

	uint32 m_beginTime;
	uint32 m_relicHolderSteps;

	// CAPTURE
	void PlayerDropRelic(CClient * player);
	void PlayerGetRelic(CClient * player);
	CClient * GetRelicHolder()				const { return _relicHolder; }
	bool IsRelicGenuine(CItem * relic)	const { return (_relic == relic) ? TRUE : FALSE; }
	const Point GetRelicPos()				const { return _relicPos; }

	// DESTROY_SHIELD
	bool ShieldDestroyed();

protected:
	const EventType _eventType;

	Casualties _sideStats[MAXSIDES];

	// CAPTURE
	CItem * _relic;
	Point _relicPos;
	CClient * _relicHolder;
	Side _relicOwnedSide;	// Side that possesses relic in altar
	uint32 _relicOwnedTime;

	void _CaptureStart();
	bool _IsRelicInAltar();
	void _CaptureEnd();

	// DESTROY_SHIELD
	uint32 _shieldCount;
};

typedef	std::auto_ptr<CAstoria>	Astoria;

#endif