#include "windows.h"
#include "defs.hpp"
#include <windowsx.h>
#include <winuser.h>
#include <mmsystem.h>
#include <stdio.h>
#include "net\XSocket.h"
#include "main.h"
#include "net\MsgCodes.h"
#include "LoginServer.h"
#include "DIRECT.H"
//=============================================================================
char					szAppClass[32];
HWND					hWnd = NULL;
HINSTANCE				hInst = NULL;
BOOL                    MsgUpdated = FALSE, IsOnCloseProcess = FALSE;
RECT                    rctSrvList, SepRect;
MMRESULT                Timer = NULL;
XSocket                 *MainSocket, *GateServerSocket, *GameServerSocket[MAXGAMESERVERSOCKETS], *ClientSocket[MAXCLIENTS];
CLoginServer	        *Server = NULL;
BYTE                    ConnectedHGServers;
WORD                    PeakPeopleOnline, ActiveAccounts;
DWORD                   TotalAccounts;
HANDLE					hMutex;
//=============================================================================
MYSQL mySQL;
BYTE MySqlAutoFixNum = 1;
//=============================================================================
struct sMsg
{
	char Message[MAXLOGMSGS][MAXLOGMSGSIZE];
	BYTE MsgLvl[MAXLOGMSGS];
	WORD CurMsg;
}LogMsg;
//=============================================================================
void UpdateScreen()
{
	if (MsgUpdated == TRUE){
		InvalidateRect(hWnd, NULL, TRUE);
		MsgUpdated = FALSE;
	}
}
//=============================================================================
void PutLogFileList(char * cStr, char *FileName)
{
	char Txt[50], FName[100];
	FILE * pFile;
	char cBuffer[MAXLOGLINESIZE+100];
	SYSTEMTIME SysTime;

	if(strlen(cStr) > MAXLOGLINESIZE) return;
	GetLocalTime(&SysTime);

	_mkdir("Logs");

	if(FileName == NULL) 
		pFile = fopen("Events.log", "at");
	else if(IsSame(FileName, GM_LOGFILE)){
		_mkdir("Logs/GM");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "GM Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if(IsSame(FileName, PLAYER_LOGFILE)){
		_mkdir("Logs/Player");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "Player Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if(IsSame(FileName, ITEM_LOGFILE)){
		_mkdir("Logs/Item");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "Item Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if(IsSame(FileName, CRUSADE_LOGFILE)){
		_mkdir("Logs/Crusade");
		ZeroMemory(Txt, sizeof(Txt));
		ZeroMemory(FName, sizeof(FName));
		sprintf(Txt, "Crusade Events %4d-%02d-%02d.log", SysTime.wYear, SysTime.wMonth, SysTime.wDay);
		SafeCopy(FName, FileName);
		strcat(FName, Txt);
		pFile = fopen(FName, "at");
	}
	else if(IsSame(FileName, XSOCKET_LOGFILE) || IsSame(FileName, GSPACKET_LOGFILE) || IsSame(FileName, CLIENTPACKET_LOGFILE) ||
		IsSame(FileName, GSUNKNOWNMSG_LOGFILE) || IsSame(FileName, CLIENTUNKNOWNMSG_LOGFILE)) 
		pFile = fopen(FileName, "ab");
	else 
		pFile = fopen(FileName, "at");

	if (pFile == NULL) return;

	ZeroMemory(cBuffer, sizeof(cBuffer));

	sprintf(cBuffer, "(%4d:%02d:%02d:%02d:%02d) - ", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	strcat(cBuffer, cStr);
	strcat(cBuffer, "\n");

	fwrite(cBuffer, 1, strlen(cBuffer), pFile);
	fclose(pFile);
}
//=============================================================================
void PutLogList(char * cMsg, BYTE MsgLvl, BOOL PutOnFile, char *FileName)
{
	if(strlen(cMsg) <= MAXLOGMSGSIZE)
	{
		MsgUpdated = TRUE;
		LogMsg.CurMsg++;
		if(LogMsg.CurMsg >= MAXLOGMSGS) LogMsg.CurMsg = 0;
		ZeroMemory(LogMsg.Message[LogMsg.CurMsg], sizeof(LogMsg.Message[LogMsg.CurMsg]));
		SafeCopy(LogMsg.Message[LogMsg.CurMsg], cMsg);
		LogMsg.MsgLvl[LogMsg.CurMsg] = MsgLvl;
		UpdateScreen();
	}
	else if(strlen(cMsg) > MAXLOGLINESIZE) return;
	//if(PutOnFile == TRUE)
		PutLogFileList(cMsg, FileName);
}
//=============================================================================
void OnPaint()
{
	HDC hdc;
	PAINTSTRUCT ps;
	register short i;
	BYTE ServerListIndex = 0;
	char Txt100[100], CurMsg;

	hdc = BeginPaint(hWnd, &ps);

	SetBkMode(hdc,TRANSPARENT);
	SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
	FillRect(hdc, &rctSrvList, (HBRUSH)(3));
	FillRect(hdc, &SepRect, (HBRUSH)(7));

	CurMsg = (char)LogMsg.CurMsg;
	for (i = 0; i <= MAXLOGSTOSHOW; i++){
		if(CurMsg < 0) CurMsg = (MAXLOGMSGS-1);
		if (strlen(LogMsg.Message[CurMsg]) != NULL){
			switch(LogMsg.MsgLvl[CurMsg]){
			case WARN_MSG:
				SetTextColor(hdc, clMaroon);
				break;

			case INFO_MSG:
				SetTextColor(hdc, clNavy);
				break;	

			default:
				SetTextColor(hdc, clBlack);
				break;
			}
			TextOut(hdc, 5, (MAXLOGSTOSHOW*14)-(i*14)+4, LogMsg.Message[CurMsg], strlen(LogMsg.Message[CurMsg]));
		}
		CurMsg --;
	}
	SetTextColor(hdc, RGB(255, 255, 255));
	TextOut(hdc, 500, 4, "* Active GameServers *", 22);
	if(Server != NULL){
		for(WORD w = 0; w < MAXGAMESERVERS; w++){
			if(Server->GameServer[w] != NULL){
				ZeroMemory(Txt100, sizeof(Txt100));
				sprintf(Txt100, "%s - %s", Server->GameServer[w]->WorldName, Server->GameServer[w]->ServerName);
				if(Server->GameServer[w]->IsBeingClosed || !Server->GameServer[w]->IsInitialized) SetTextColor(hdc, clMaroon);
				else SetTextColor(hdc, RGB(255, 255, 255));
				TextOut(hdc, 465, 30 + 14*ServerListIndex, Txt100, strlen(Txt100));
				ServerListIndex++;
				if(ServerListIndex == ConnectedHGServers) break;
			}
		}
	}
	SetTextColor(hdc, RGB(255, 255, 255));

	ZeroMemory(Txt100, sizeof(Txt100));
	sprintf(Txt100, "Accounts: [%lu]", TotalAccounts);
	TextOut(hdc, 560, 30, Txt100, strlen(Txt100));
	ZeroMemory(Txt100, sizeof(Txt100));
	sprintf(Txt100, "Total playing: [%u]", ActiveAccounts);
	TextOut(hdc, 560, 44, Txt100, strlen(Txt100));
	ZeroMemory(Txt100, sizeof(Txt100));
	sprintf(Txt100, "Max. playing: [%u]", PeakPeopleOnline);
	TextOut(hdc, 560, 58, Txt100, strlen(Txt100));
	EndPaint(hWnd, &ps);
}
//=============================================================================
void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2)
{
	Server->OnTimer();
}
//=============================================================================
MMRESULT _StartTimer(DWORD dwTime)
{
	TIMECAPS caps;
	MMRESULT timerid;

	timeGetDevCaps(&caps, sizeof(caps));
	timeBeginPeriod(caps.wPeriodMin);
	timerid = timeSetEvent(dwTime,0,_TimerFunc,0, (UINT)TIME_PERIODIC);

	return timerid;
}
//=============================================================================
void _StopTimer(MMRESULT timerid)
{
	TIMECAPS caps;

	if (timerid != 0) {
		timeKillEvent(timerid);
		timerid = 0;
		timeGetDevCaps(&caps, sizeof(caps));
		timeEndPeriod(caps.wPeriodMin);
	}
}
//=============================================================================
void OnDestroy()
{
	SAFEDELETE(Server);
	PostQuitMessage(0);
}
//=============================================================================
int CALLBACK LoginDlgProc( HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam )
{
	switch (msg)
	{

	case WM_INITDIALOG:
		SetFocus (GetDlgItem (hDlg, IDC_EDIT1));
		break;

	case WM_COMMAND:
		switch( LOWORD(wParam) )
		{
		case IDCANCEL:
			EndDialog( hDlg, TRUE );
			OnDestroy();
			return TRUE;

		case IDOK:
			if(Server == NULL) throw "Unknown error occured! Server = NULL";
			GetDlgItemText(hDlg, IDC_EDIT1, Server->mySqlUser, 20);
			GetDlgItemText(hDlg, IDC_EDIT2, Server->mySqlPwd, 20);
			UINT iResult = 0;
			mysql_init(&mySQL);
			if(!mysql_real_connect(&mySQL, Server->mySqlAddress, Server->mySqlUser, Server->mySqlPwd, "helbreath", Server->mySqlPort, NULL, NULL)){
				iResult = Server->MyAux_Get_Error(&mySQL);
				mysql_close(&mySQL);
			}
			if(iResult != NULL){
				if(iResult == 2003) PutLogList("(ERROR) mySql server seems to be offline, please check the IP", WARN_MSG);
				SetDlgItemText(hDlg, IDC_EDIT1, NULL);
				SetDlgItemText(hDlg, IDC_EDIT2, NULL);
				SetFocus (GetDlgItem (hDlg, IDC_EDIT1));
				mysql_close(&mySQL);
				return TRUE;
			}
			PutLogList("-Connection to mySQL database was sucessfully established!");
			EndDialog( hDlg, TRUE );
			if(!Server->InitServer()) SAFEDELETE(Server);
			break;
		}
		break;
	}

	return FALSE;
}
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam )
{
	switch (message) {

	case WM_CLOSE:
		IsOnCloseProcess = TRUE;
		if (MessageBox(NULL, "Player data not saved! Shutdown server now?", "Shutdown?", MB_ICONEXCLAMATION | MB_YESNO) == IDYES)
		{
			SAFEDELETE(Server);
			exit(EXIT_SUCCESS);
		}
		else IsOnCloseProcess = FALSE;
		break;

	case WM_PAINT:
		OnPaint();
		break;

	case WM_KEYDOWN:
		if(Server) Server->OnKeyDown(wParam);
		return(DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_KEYUP:
		if(Server) Server->OnKeyUp(wParam);
		return(DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_DESTROY:
		OnDestroy();
		break;

	case WM_USER_ACCEPT:
		Server->OnUserAccept(hWnd);
		break;

	case WM_GATESERVER_ACCEPT:
		Server->OnGateServerAccept(hWnd);
		break;

	default:
		if ((message >= WM_ONCLIENTSOCKETEVENT) && (message < WM_ONCLIENTSOCKETEVENT + MAXCLIENTS))
			Server->OnClientSocketEvent(message, wParam, lParam);

		else if ((message >= WM_ONGAMESERVERSOCKETEVENT) && (message < WM_ONGAMESERVERSOCKETEVENT + MAXGAMESERVERSOCKETS))
			Server->OnGameServerSocketEvent(message, wParam, lParam);

		else return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return NULL;
}
//=============================================================================
BOOL InitApplication( HINSTANCE hInstance)
{
	WNDCLASS  wc;

	wc.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC);
	wc.lpfnWndProc   = (WNDPROC)WndProc;
	wc.cbClsExtra    = 0;
	wc.cbWndExtra    = sizeof (int);
	wc.hInstance     = hInstance;
	wc.hIcon         = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(6);
	wc.lpszMenuName  = NULL;
	wc.lpszClassName = szAppClass;

	return (RegisterClass(&wc));
}
//=============================================================================
BOOL InitInstance( HINSTANCE hInstance, int nCmdShow )
{
	char cTitle[100];
	SYSTEMTIME SysTime;
	GetLocalTime(&SysTime);

	sprintf(cTitle, "Helbreath Login Server V.%d.%d Started On:(%4d:%02d:%02d:%02d:%02d)", UPPER_VERSION, LOWER_VERSION, SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	hWnd = CreateWindowEx(0,
		szAppClass,
		cTitle,
		WS_VISIBLE |
		WS_POPUP |
		WS_CAPTION |
		WS_SYSMENU |
		WS_MINIMIZEBOX,
		100,
		100,
		680,
		300,
		NULL,
		NULL,
		hInstance,
		NULL );

	if (!hWnd) return (FALSE);

	UpdateWindow(hWnd);

	return (TRUE);
}
//=============================================================================
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
	LPSTR lpCmdLine, int nCmdShow )
{
#ifndef _DEBUG
	hMutex = CreateMutex( NULL, FALSE, "HB LoginServer." ); // Create a Mutex 
	if ( ( hMutex == NULL ) || ( GetLastError() == ERROR_ALREADY_EXISTS ) ) {
		MessageBox(GetForegroundWindow(), "Login server is already opened!", "Login server", MB_OK|MB_ICONWARNING);
		CloseHandle( hMutex ); 
		return FALSE; 
	}
#endif

	LogMsg.CurMsg = MAXLOGMSGS-1;
	sprintf( szAppClass, "LoginServer%d", hInstance);
	if (!InitApplication( hInstance))		return (FALSE);
	if (!InitInstance(hInstance, nCmdShow)) return (FALSE);
	hInst = hInstance;

	SetRect(&rctSrvList, 460, 0, 800, 300);//blue
	SetRect(&SepRect, 456, 0, 460, 300);//devider
	MSG Message;
	Server = new CLoginServer();
	if(!Server->DoInitialSetup()) SAFEDELETE(Server);
	while(1)
	{
		if ( PeekMessage( &Message, NULL, 0, 0, PM_NOREMOVE ))
		{
			if ( !GetMessage( &Message, NULL, 0, 0 )) return static_cast<int>( Message.wParam );
			TranslateMessage( &Message );
			DispatchMessage( &Message );
			UpdateScreen();
		}
		else WaitMessage( );
	}
	return 0;
}
//=============================================================================
BYTE Retrive8ByteValue(char * cp, DWORD offset)
{
	char   *pcp;
	BYTE	*bp;

	pcp = (char *)cp;
	pcp += offset;
	bp = (BYTE *)pcp;
	return *bp;
}
//=============================================================================
WORD Retrive16WordValue(char * cp, DWORD offset)
{
	char   *pcp;
	WORD	*wp;

	pcp = (char *)cp;
	pcp += offset;
	wp = (WORD *)pcp;
	return *wp;
}
//=============================================================================
DWORD Retrive32DWordValue(char * cp, DWORD offset)
{
	char   *pcp;
	DWORD	*dwp;

	pcp = (char *)cp;
	pcp += offset;
	dwp = (DWORD *)pcp;
	return *dwp;
}

uint64 Retrive64DWordValue(char * cp, DWORD offset)
{
	char   *pcp;
	uint64	*dwp;

	pcp = (char *)cp;
	pcp += offset;
	dwp = (uint64 *)pcp;
	return *dwp;
}
//=============================================================================
void SendValue(char * cp, DWORD offset, BYTE size, uint64 value)
{
	BYTE   *bp;
	WORD   *wp;
	DWORD  *dwp;
	uint64  *llp;
	char   *pcp;

	pcp = (char *)cp;
	pcp += offset;
	switch(size)
	{
	case BYTESIZE:
		bp = (BYTE *)pcp;
		*bp = (BYTE)value;
		break;
	case WORDSIZE:
		wp = (WORD *)pcp;
		*wp = (WORD)value;
		break;
	case DWORDSIZE:
		dwp = (DWORD *)pcp;
		*dwp = (DWORD)value;
		break;
	case I64SIZE:
		llp = (UINT64 *)pcp;
		*llp = value;
		break;
	}
}
//=============================================================================
void SafeCopy(char *c1, char *c2, DWORD lenght)
{
	register DWORD d;

	if(lenght == 0){
		d = 0;
		if(c2[d] == NULL) return;
		while(c2[d] != NULL){
			c1[d] = c2[d];
			d++;
		}
	}
	else for(d = 0; d < lenght; d++) c1[d] = c2[d];

	c1[d] = NULL;
}
//=============================================================================
BOOL IsSame(char *c1, char *c2)
{
	DWORD size1, size2;

	size1 = strlen(c1);
	size2 = strlen(c2);
	if(size1 == size2 && memcmp(c1, c2, size1) == 0) return true;
	else return false;
}
//=============================================================================
void MakeGoodName(char *dest, char *source)
{
	DWORD size, d;
	char *cp;

	size = strlen(source);
	if(size == 0) return;
	d = 0;
	cp = (char *)dest;
	while(source[d] != NULL){
		if(	source[d] == '\'' || source[d] == '\\' || source[d] == '\"'){

			cp[0] = '\\';
			cp++;
			cp[0] = source[d];
			cp++;
		}
		else{
			cp[0] = source[d];
			cp++;
		}
		d++;
	}
}
//=============================================================================
void Delay(DWORD nTimeMs)
{
	MSG msg;
	DWORD endTick;

	endTick = GetTickCount() + nTimeMs;
	while(GetTickCount() < endTick){
		if(PeekMessage(&msg, NULL, 0, 0, TRUE)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return;
}
//=============================================================================