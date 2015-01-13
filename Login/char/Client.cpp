#include "Client.h"
//=============================================================================
CClient::CClient(char *AccName, char *AccPwd, char *CharaName, WORD CharaLevel, char *IP, BYTE GSID)
{
        ZeroMemory(AccountName, sizeof(AccountName));
        SafeCopy(AccountName, AccName);
        ZeroMemory(AccountPassword, sizeof(AccountPassword));
        SafeCopy(AccountPassword, AccPwd);
        ZeroMemory(CharName, sizeof(CharName));
        SafeCopy(CharName, CharaName);
        ZeroMemory(ClientIP, sizeof(ClientIP));
        SafeCopy(ClientIP, IP);
        ConnectedServerID = GSID;
        Time = timeGetTime();
        IsPlaying = FALSE;
        CharLevel = CharaLevel;
		IsOnServerChange = FALSE;
		ForceDisconnRequestTime = 0;
		ActiveAccounts++;
		if(ActiveAccounts > PeakPeopleOnline) PeakPeopleOnline = ActiveAccounts;
}
//=============================================================================
CClient::~CClient()
{
		if(ActiveAccounts > 0) ActiveAccounts--;
}
//=============================================================================


