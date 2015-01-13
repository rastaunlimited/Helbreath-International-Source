#ifndef _DEFS_HPP_
#define _DEFS_HPP_

typedef char _ADDRESS[20];
typedef char CONFIG[50000];

typedef signed char     sBYTE;
typedef signed short    sWORD;
typedef signed long     sDWORD;

#define SAFEDELETE( PointerVariable )       \
{											\
    if(PointerVariable != NULL){            \
    delete PointerVariable;		    \
    PointerVariable = NULL;    }	    \
}

#define SAFEDELETEARRAY( PointerVariable )	\
{											\
    if(PointerVariable != NULL){                \
    delete [] PointerVariable;			\
    PointerVariable = NULL;    }		\
}

#define SAFEFREERESULT( PointerVariable )	\
{											\
    if(PointerVariable != NULL){                \
    mysql_free_result(PointerVariable);			\
    PointerVariable = NULL;    }		\
}

#define MAXGAMESERVERS              20
#define MAXGAMESERVERMAPS           120
#define MAXSOCKETSPERSERVER         5
#define MAXGAMESERVERSOCKETS        MAXGAMESERVERS * MAXSOCKETSPERSERVER

#define MAINTIMERSIZE               300
#define MAX_MYSQL_RESTART_ATTEMPT       5
#define MYSQL_AUTOFIX_TIMERSIZE         30000
#define MYSQL_DBOPTIMIZE_TIMERINTERVAL  10*60000
#define MYSQL_DBREPAIR_TIMERINTERVAL    15*60000
#define CHECKACCSTATUS_TIMERINTERVAL    3*60000
#define MAXWAITTIMEFORPLAYERENTERGAME   50000//30000
#define MAX_GSALIVE_WAITINTERVAL		40000//20000
#define INTERVALTOSEND_TOTALPLAYERS	5000
#define MAX_FORCEDISCONN_WAIT_TIME		12000
#define	SHUTDOWN_INTERVAL_MSG		30000
#define MAX_SERVERCHANGERESPONSE		60*1000

#define MAXCLIENTS                  500
#define MAXSKILLS                   24
#define MAXITEMS                    50
#define MAXBANKITEMS                120

#define MAXLOGMSGS                  50
#define MAXLOGMSGSIZE               400
#define MAXLOGSTOSHOW               39

//mysql query errors
#define MAXALLOWEDQUERYERROR		10

//for Msgquene
#define MSGQUENESIZE				5000

//log list message types:
#define DEFAULT_MSG                 0x00
#define WARN_MSG                    0x01
#define INFO_MSG					0x02

#define MAXLOGLINESIZE              5000

//color
#define clBlack							0x0
#define clMaroon						0x80
#define clNavy							0x800000

#define BYTESIZE                    1
#define WORDSIZE                    2
#define DWORDSIZE                   3
#define I64SIZE							4

//log files
//#define LOG_SOCKETS

#define XSOCKET_LOGFILE                 "Logs/XSocket.log"
#define GSPACKET_LOGFILE                "Logs/GS Packets.log"
#define CLIENTPACKET_LOGFILE            "Logs/Client Packets.log"
#define GM_LOGFILE						"Logs/GM/"
#define ITEM_LOGFILE                    "Logs/Item/"
#define CRUSADE_LOGFILE					"Logs/Crusade/"
#define HACK_LOGFILE                    "Logs/Hack.log"
#define TEST_LOGFILE                    "Logs/Test.log"
#define ERROR_LOGFILE                   "Logs/Error.log"
#define MYSQL_ERROR_LOGFILE             "Logs/MysqlError.log"
#define GSUNKNOWNMSG_LOGFILE            "Logs/Unknown socket msgs from gameserver.log"
#define CLIENTUNKNOWNMSG_LOGFILE        "Logs/Unknown socket msgs from client.log"
#define QUERYERROR_LOGFILE		        "Logs/Query errors.log"
#define PLAYER_LOGFILE						"Logs/Player/"
#define CLIENTUNKNOWNMSG_LOGFILE2        "Logs/Unknown_MsgIds_From_client.log"
#define GSUNKNOWNMSG_LOGFILE2            "Logs/Unknown_MsgIds_From_Gameserver.log"


//for duplied items:
#define NOITEM                      0x00
#define ONEINBAG                    0x01
#define ONEINBANK                   0x02
#define ONEINBAG_ONEINBANK          0x03
#define DUPITEMINBAG                0x04
#define DUPITEMINBANK               0x05

//login
#define ACCOUNTDONTEXISTS			0x01
#define PASSWORDISWRONG				0x02
#define LOGINOK						0x03


#endif
