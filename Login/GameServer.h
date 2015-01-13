#ifndef _GAMESERVER_H_
#define _GAMESERVER_H_

#define MAXGAMESERVERSTOCKMSGSIZE	10000

#include "net\XSocket.h"
#include "defs.hpp"
#include "net\MsgCodes.h"
//=============================================================================
class CGameServer
{
public:
		CGameServer(WORD index);
        virtual ~CGameServer();
		void SendMsg(char * cData, DWORD dwSize, char cKey, BOOL log);
		BOOL bStockMsgToGameServer(char *pData, DWORD dwSize);
		void SendStockMsgToGameServer();

        char ServerName[15], MapName[MAXGAMESERVERMAPS][15];
        _ADDRESS ServerIP;
        WORD ServerPort, InternalID;
        BYTE NumberOfMaps, ConnectedSockets;
        sWORD SocketIndex[MAXSOCKETSPERSERVER];
		DWORD AliveResponseTime, TotalPlayersResponse;
		BOOL IsInitialized, IsBeingClosed;
		char  m_cGameServerStockMsg[MAXGAMESERVERSTOCKMSGSIZE];
		int   m_iIndexGSS;
};

extern BYTE     ConnectedHGServers;
extern XSocket *GateServerSocket, *MainSocket, *GameServerSocket[MAXGAMESERVERSOCKETS];

#endif