#ifndef GLOBALH
#define GLOBALH
#pragma once

typedef signed char     sBYTE;
typedef signed short    sWORD;
typedef signed long     sDWORD;

#ifdef _DEBUG
#define DEBUGMODE
#endif

#ifdef DEBUGMODE
	//#define NO_SECONDDROP
	//#define LOG_ARMORSTATS
	//#define ALLOWPLAYERTP
#endif

#define	TICKDELAY					15 _ms
#define NO_MSGSPEEDCHECK

#define SAFEDELETE( PointerVariable ){if(PointerVariable != NULL){delete PointerVariable;PointerVariable = NULL;}}
#define SAFEDELETEARRAY( PointerVariable ){if(PointerVariable != NULL){delete [] PointerVariable;PointerVariable = NULL;}}

#define BYTESIZE                    1
#define WORDSIZE                    2
#define DWORDSIZE                   3
#define I64SIZE							4

enum Sex{
	NONE,
	MALE,
	FEMALE
};

#define K		16	// Used for Elo system

//log files
#define XSOCKET_LOGFILE                 "Logs/XSocket.log"
#define ADMIN_LOGFILE                   "Logs/Admin.log"
#define PVP_LOGFILE						"Logs/PvP.log"
#define ITEM_LOGFILE                    "Logs/Item.log"
#define HACK_LOGFILE                    "Logs/Hack.log"
#define TEST_LOGFILE                    "Logs/Test.log"
#define ERROR_LOGFILE                   "Logs/Error.log"
#define DEBUG_LOGFILE                   "Logs/Debug.log"
#define EVENT_LOGFILE                   "Logs/Events.log"
#define GSUNKNOWNMSG_LOGFILE            "Logs/Unknown socket msgs from gameserver.log"
#define CLIENTUNKNOWNMSG_LOGFILE        "Logs/Unknown socket msgs from client.log"

//color
#define clBlack							0x0
#define clMaroon						0x80
#define clNavy							0x800000

#define MAXLOGMSGS                  50
#define MAXLOGMSGSIZE               300
#define MAXLOGSTOSHOW               39

#define DEFAULT_MSG                 0x00
#define WARN_MSG                    0x01
#define INFO_MSG					0x02

#define MAXLOGLINESIZE              1000

#define MSGBUFFERSIZE				30000

#define BISLEGOLDCOST				100
#define ARENAGOLDCOST				250
#define DGLV2GOLDCOST				2500

#define RAIDTIME				60

//=============================================================================
#define GOLDDROPMULTIPLIER			1
#define EXPMULTIPLIER				150
//=============================================================================
//#define WEAPONSPEEDLIMIT
#define MAXCRUSADESTRUCTURES		300
#define MAXAGRICULTURE				200

//#define CHECKUSERNPCNUM	
//#define GUILDWARMODE

#define BEGINNERTOWNPROTECT

#define MAXRECALLTIME


// #define TAIWANLOG
// #define LOGTIME
// #define PKPENALTY
// #define SAMESIDETOWNPROTECT
// #define ITEMDROP

#endif GLOBALH