#include "GameServer.h"
//==============================================================================
CGameServer::CGameServer(WORD index)
{
 char *cp;
 DWORD *dwp;
 WORD *wp;

			for(BYTE b = 0; b < MAXSOCKETSPERSERVER ; b++) SocketIndex[b] = -1;
			GameServerSocket[index]->GSSocketID = 0;
            GameServerSocket[index]->IsRegistered = TRUE;
            SocketIndex[0] = index;
            ConnectedSockets = 1;
			ConnectedHGServers++;
			InternalID = 0;
			IsInitialized = IsBeingClosed = FALSE;
			AliveResponseTime = timeGetTime();
			ZeroMemory(m_cGameServerStockMsg, sizeof(m_cGameServerStockMsg));
			cp = (char *)m_cGameServerStockMsg;
			dwp = (DWORD *)cp;
			*dwp = MSGID_SERVERSTOCKMSG;
			cp += 4;
			wp = (WORD *)cp;
			*wp = MSGTYPE_CONFIRM;
			cp += 2;

			m_iIndexGSS = 6;

}
//==============================================================================
CGameServer::~CGameServer()
{
 char Txt100[100];

        for(BYTE b = 0; b < MAXSOCKETSPERSERVER ; b++)
           {
            if(SocketIndex[b] < 0) continue;
			SAFEDELETE(GameServerSocket[SocketIndex[b]]);
            SocketIndex[b] = -1;
           }
        ZeroMemory(Txt100, sizeof(Txt100));
        wsprintf(Txt100, "(!!!) GameServer [%s] connection was lost!", ServerName);
        PutLogList(Txt100, WARN_MSG);
		ConnectedHGServers--;
}
//==============================================================================
void CGameServer::SendMsg(char * cData, DWORD dwSize, char cKey, BOOL log)
{
 if(SocketIndex[0] < 0) return;
 if(GameServerSocket[SocketIndex[0]] != NULL) GameServerSocket[SocketIndex[0]]->iSendMsg(cData, dwSize, cKey, log);
}
//=============================================================================
BOOL CGameServer::bStockMsgToGameServer(char *pData, DWORD dwSize)
{
 char * cp;

	if ((m_iIndexGSS + dwSize) >= MAXGAMESERVERSTOCKMSGSIZE-10) return FALSE;

	cp = (char *)(m_cGameServerStockMsg + m_iIndexGSS);	
	SafeCopy(cp, pData, dwSize);

	m_iIndexGSS += dwSize;

	return TRUE;
}
//=============================================================================
void CGameServer::SendStockMsgToGameServer()
{
 DWORD * dwp;
 WORD * wp;
 char * cp;

	if (m_iIndexGSS > 6) {
		SendMsg(m_cGameServerStockMsg, m_iIndexGSS, NULL, FALSE);
	
		ZeroMemory(m_cGameServerStockMsg, sizeof(m_cGameServerStockMsg));
		cp = (char *)m_cGameServerStockMsg;
		dwp = (DWORD *)cp;
		*dwp = MSGID_SERVERSTOCKMSG;
		cp += 4;
		wp = (WORD *)cp;
		*wp = MSGTYPE_CONFIRM;
		cp += 2;

		m_iIndexGSS = 6;
	}
}
//=============================================================================