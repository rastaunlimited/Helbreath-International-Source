#ifndef COMMON_H
#define COMMON_H
#pragma once

#include	<iostream>
#include	<sstream>
#include <memory>
#include	"version.h"
#include	"typedefs.h"
#include	"lgnSvcs.h"

#define	MAXPARTYMEMBERS	25
#define	MAXSIDES			4

enum Side
{
	NEUTRAL,
	ARESDEN,
	ELVINE,
	ISTRIA,
	HOSTILE
};

static const char * sideName[MAXSIDES] = { "Traveller", "Aresden", "Elvine", "Istria" };
static const char * sideMap[MAXSIDES] = { "default", "aresden", "elvine", /*"istria"*/"default2" };
static const char * sideMapJail[MAXSIDES] = { "default", "arejail", "elvjail", /*"istjail"*/"default2" };
static const char * sideMapFarm[MAXSIDES] = { "default", "arefarm", "elvfarm", /*"istfarm"*/"default2" };
static const char * sideMapRes[MAXSIDES] = { "default", "resurr1", "resurr2", /*"resurr3"*/"default2" };

enum chatTypes
{
	CHAT_NORMAL,
	CHAT_GUILD,
	CHAT_SHOUT,
	CHAT_NATIONSHOUT,
	CHAT_PARTY,
	CHAT_GM = 10,
	CHAT_WHISPER = 20
};

enum StatusFlags
{
	STATUS_INVISIBILITY =		1 << 4,	// 0x00000010
	STATUS_BERSERK =				1 << 5,	// 0x00000020
	STATUS_FROZEN =				1 << 6,	// 0x00000040
	STATUS_POISON =				1 << 7,	// 0x00000080

	STATUS_ANGELSTR =				1 << 12,	// 0x00001000
	STATUS_ANGELDEX =				1 << 13,	// 0x00002000
	STATUS_ANGELINT =				1 << 14,	// 0x00004000
	STATUS_ANGELMAG =				1 << 15,	// 0x00008000

	STATUS_RELICHOLDER = 		1 << 17,	// 0x00020000 - previously STATUS_HEROFLAG
	STATUS_AFK =					1 << 18,	// 0x00040000
	STATUS_GREENSLATE =			1 << 16,	// 0x00010000
	STATUS_REDSLATE =				1 << 22,	// 0x00400000
	STATUS_BLUESLATE =			1 << 23,	// 0x00800000
	STATUS_ILLUSIONMOVEMENT =	1 << 21,	// 0x00200000
	STATUS_ILLUSION =				1 << 24,	// 0x01000000
	STATUS_DEFENSESHIELD =		1 << 25,	// 0x02000000
	STATUS_PFM =					1 << 26,	// 0x04000000
	STATUS_PFA =					1 << 27,	// 0x08000000
	STATUS_PK =						1 << 20,	// 0x00100000
	// Moved to a 4-bit variable
	//STATUS_ISTRIA =				1 << 28,	// 0x10000000
	//STATUS_ARESDEN =			1 << 29,	// 0x20000000
	//STATUS_CITIZEN =			1 << 30,	// 0x40000000
	STATUS_SIDE =					0xF0000000,
	STATUS_ALL =					0xFFFFFFFF,
	STATUS_ENEMYFLAGS =			STATUS_ALL - ( STATUS_PFA | 
												STATUS_PFM |
												STATUS_DEFENSESHIELD |
												STATUS_ILLUSION |
												STATUS_POISON )
};

enum GMFlags
{
	GMFLAG_INVENCIBLE =		1,
	GMFLAG_NOAGGRO =				1 << 1
};

//#define SECONDS(x)			(x * CLOCKS_PER_SEC)
//#define MINUTES(x)			(x * SECONDS(60))
//#define HOURS(x)			(x * MINUTES(60))
//#define DAYS(x)				(x * HOURS(24))

// Time
#define _ms					_s / 1000
#define _s					* CLOCKS_PER_SEC
#define _m					_s * 60
#define _h					_m * 60
#define _d					_h * 24

enum DaysOfWeek
{
	SUNDAY,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};


#define RELICVICTORYTIME		(10 _m)

enum EventType{
	ET_NONE, 
	ET_CAPTURE, 
	ET_DESTROY_SHIELD,
	ET_CRUSADE,
	ET_MAX
};
static const char * eventName[] = { "", "Capture the Relic", "Destroy the Shield", "Crusade" };

struct Casualties{
	uint32 deaths;
	uint32 kills;
};



enum HeroReq{
	HR_CAPE,
	HR_HELM,
	HR_CAP,
	HR_PLATE,
	HR_ROBE,
	HR_HAUBERK,
	HR_LEGGINGS,
	HR_MAX
};

static const struct HeroItemCost{
	uint32 EK;
	uint32 contribution;
}heroPrice[HR_MAX] = 
{
	{300,0},		// HR_CAPE
	{150,20},	// HR_HELM
	{100,20},	// HR_CAP
	{300,30},	// HR_PLATE
	{200,20},	// HR_ROBE
	{100,10},	// HR_HAUBERK
	{150,15}		// HR_LEGGINGS
};

static const uint32 HeroItemID[HR_MAX][MAXSIDES-1][2] =
{
	{	// HR_CAPE
		{400, 400},		// ARESDEN
		{401, 401},		// ELVINE
		{1009, 1009}	// ISTRIA
	},
	{	// HR_HELM
		{403, 404},		// ARESDEN
		{405, 406},		// ELVINE
		{1010, 1011}	// ISTRIA
	},
	{	// HR_CAP
		{407, 408},		// ARESDEN
		{409, 410},		// ELVINE
		{1012, 1013}	// ISTRIA
	},
	{	// HR_PLATE
		{411, 412},		// ARESDEN
		{413, 414},		// ELVINE
		{1014, 1015}	// ISTRIA
	},
	{	// HR_ROBE
		{415, 416},		// ARESDEN
		{417, 418},		// ELVINE
		{1016, 1017}	// ISTRIA
	},
	{	// HR_HAUBERK
		{419, 420},		// ARESDEN
		{421, 422},		// ELVINE
		{1018, 1019}	// ISTRIA
	},
	{	// HR_LEGGINGS
		{423, 424},		// ARESDEN
		{425, 426},		// ELVINE
		{1020, 1021}	// ISTRIA
	}
};





#define atoul(str)	strtoul(str, NULL, 10)
#define atoull(str)	_strtoui64(str, NULL, 10)

#define logb(n, b)	(log(n)/log(b))


struct Point{
	int32 x,y;

	bool operator ==(Point p)
	{
		return (p.x == x && p.y == y) ? TRUE : FALSE;
	}
};

#endif //COMMON_H