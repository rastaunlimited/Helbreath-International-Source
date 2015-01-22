#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <winbase.h>
#include <mmsystem.h>
#include <time.h>		   
#include "winmain.h"
#include "..\HG.h"
#include "..\net\UserMessages.h"
#include "..\GlobalDef.h"
#include "..\res\Resource.h"

// --------------------------------------------------------------

#define WM_USER_TIMERSIGNAL		WM_USER + 500

// Listbox
static HWND    List1;
static HWND    Edit1;
static HWND    Button1;
static HWND    Button2;
static HWND    Button3;
static HINSTANCE BCX_hInstance;
static int     BCX_ScaleX;
static int     BCX_ScaleY;
static char    BCX_ClassName[2048];
HWND    BCX_Listbox(char*,HWND,int,int,int,int,int,int=0,int=-1);
HWND    BCX_Editbox(char*,HWND,int,int,int,int,int,int=0,int=-1);
HWND    BCX_Button(char*,HWND,int,int,int,int,int,int=0,int=-1);
void ParseCommand(char*);
int ItemCount=0;
bool scrolling = true;


char			szAppClass[32];
HWND			G_hWnd = NULL;
char			G_cMsgList[120*50];
bool            G_cMsgUpdated =	FALSE;
char            g_cTxt[512];
char            g_msg[50];
char			G_cData50000[50000];
MMRESULT        G_mmTimer = NULL;

char			G_cLogBuffer[30000] ;
short			G_sLogCounter ;
DWORD			G_dwLogTime ; 


class XSocket * G_pListenSock = NULL;
class XSocket * G_pLogSock    = NULL;
class CGame *   g_game       = NULL;

class CMap	**	g_mapList	= NULL;
class CClient ** g_clientList = NULL;
class CNpc **	g_npcList = NULL;
class CNpc **   g_npcConfigList = NULL;
class CMagic ** g_magicConfigList = NULL;

int * g_skillSSNpoint = NULL;

int             G_iQuitProgramCount = 0;
bool            G_bShutdown = FALSE; 

RECT            rctSrvList;

//=============================================================================
struct sMsg
{
        char Message[MAXLOGMSGS][MAXLOGMSGSIZE];
        BYTE MsgLvl[MAXLOGMSGS];
        WORD CurMsg;
}LogMsg;
//=============================================================================
LRESULT CALLBACK WndProc( HWND hWnd,UINT message,WPARAM wParam,LPARAM lParam )
{ 
	switch (message) {
	case WM_COMMAND:
		switch(wParam){
		case 1012:	// Toggle scrolling
			if(scrolling)
				scrolling = false;
			else
				scrolling = true;
			break;
		case 1013:	// Clear
			SendMessage(List1,(UINT)LB_RESETCONTENT,0,0);
			ItemCount = 0;
			break;
		case 1010:	// OK
			//CreateBitmap(1,1,1,1,1);
			char commandtxt[100];
			GetWindowText(Edit1,commandtxt,100);
			if (commandtxt != NULL) {
				SetWindowText(Edit1,NULL);
				SetFocus(Edit1);
				parseCommand(commandtxt);
			}
			break;
		}
		break;

	case WM_CREATE:
		break;

	case WM_KEYDOWN:
		g_game->OnKeyDown(wParam, lParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_KEYUP:
		g_game->OnKeyUp(wParam, lParam);
		return (DefWindowProc(hWnd, message, wParam, lParam));
		break;

	case WM_USER_STARTGAMESIGNAL:
		g_game->OnStartGameSignal();
		break;

	case WM_USER_TIMERSIGNAL:
	    if(G_bShutdown == FALSE) g_game->OnTimer(NULL);
		break;

	case WM_USER_ACCEPT:
		OnAccept();
		break;

	//case WM_KEYUP:
	//	OnKeyUp(wParam, lParam);
	//	break;

	case WM_PAINT:
		OnPaint();
		break;

	case WM_DESTROY:
		G_bShutdown = TRUE ;
		OnDestroy();
		break;

	case WM_CLOSE:
		if (g_game->bOnClose() == TRUE) return (DefWindowProc(hWnd, message, wParam, lParam));
		//G_iQuitProgramCount++;
		//if (G_iQuitProgramCount >= 2) {
		//	return (DefWindowProc(hWnd, message, wParam, lParam));
		//}
		break;

	default: 
		if ( G_bShutdown == TRUE) break;
		if (message == WM_ONWEBSOCKETEVENT)
			g_game->OnWebSocketEvent(message, wParam, lParam);

		if ((message >= WM_ONLOGSOCKETEVENT + 1) && (message <= WM_ONLOGSOCKETEVENT + MAXSUBLOGSOCK))
			g_game->OnSubLogSocketEvent(message, wParam, lParam);

		if ((message >= WM_ONCLIENTSOCKETEVENT) && (message < WM_ONCLIENTSOCKETEVENT + MAXCLIENTS)) 
			g_game->OnClientSocketEvent(message, wParam, lParam);

		return (DefWindowProc(hWnd, message, wParam, lParam));
	}

	return NULL;
}
//=============================================================================
int APIENTRY WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance,
               LPSTR lpCmdLine, int nCmdShow )
{
	LogMsg.CurMsg = MAXLOGMSGS-1;
	sprintf( szAppClass, "GameServer%d", hInstance);
	if (!InitApplication( hInstance))		return (FALSE);
    if (!InitInstance(hInstance, nCmdShow)) return (FALSE);

	Initialize();
	EventLoop();
    return 0;
}
//=============================================================================
bool InitApplication( HINSTANCE hInstance)
{     
 WNDCLASS  wc;

	wc.style = (CS_HREDRAW | CS_VREDRAW | CS_OWNDC | CS_DBLCLKS);
	wc.lpfnWndProc   = (WNDPROC)WndProc;             
	wc.cbClsExtra    = 0;                            
	wc.cbWndExtra    = sizeof (int);             
	wc.hInstance     = hInstance;                    
	wc.hIcon         = LoadIcon( hInstance, MAKEINTRESOURCE(IDI_ICON1) );
	wc.hCursor       = LoadCursor(NULL, IDC_ARROW);  
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);	 
	wc.lpszMenuName  = NULL;                    		 
	wc.lpszClassName = szAppClass;                   
     
	SetRect(&rctSrvList, 600, 0, 602, 600);

	return (RegisterClass(&wc)) ? TRUE : FALSE;
}
//=============================================================================
bool InitInstance( HINSTANCE hInstance, int nCmdShow )
{
 char cTitle[100];
 SYSTEMTIME SysTime;

	GetLocalTime(&SysTime);
	wsprintf(cTitle, "Helbreath Map Server V.%d.%d (Executed at %.2d:%.2d on %d/%.2d)", UPPER_VERSION, LOWER_VERSION, SysTime.wHour, SysTime.wMinute, SysTime.wDay, SysTime.wMonth);

	G_hWnd = CreateWindowEx(0,
        szAppClass,
        cTitle,
        WS_VISIBLE |
        WS_SYSMENU |
        WS_MINIMIZEBOX,
		100,
        100,
        800,
        400,
        NULL,
        NULL,
        hInstance,
        NULL );

    if (!G_hWnd) return (FALSE);

	WNDCLASS Wc;
	strcpy(BCX_ClassName,"ListBox1");
	BCX_ScaleX       = 1;
	BCX_ScaleY       = 1;
	BCX_hInstance    =  hInstance;
	Wc.style         =  CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	Wc.lpfnWndProc   =  WndProc;
	Wc.cbClsExtra    =  0;
	Wc.cbWndExtra    =  0;
	Wc.hInstance     =  hInstance;
	Wc.hIcon         =  LoadIcon(NULL,IDI_WINLOGO);
	Wc.hCursor       =  LoadCursor(NULL,IDC_ARROW);
	Wc.hbrBackground =  (HBRUSH)(COLOR_BTNFACE+1);
	Wc.lpszMenuName  =  NULL;
	Wc.lpszClassName =  BCX_ClassName;
	RegisterClass(&Wc);

	List1=BCX_Listbox("",G_hWnd,1009,0,0,600,330);
	Edit1=BCX_Editbox("",G_hWnd,1011,0,330,600,20);
	Button1=BCX_Button("OK",G_hWnd,1010,0,350,200,20);
	Button2=BCX_Button("Toggle scrolling",G_hWnd,1012,400,350,200,20);
	Button3=BCX_Button("Clear",G_hWnd,1013,200,350,200,20);

	ShowWindow(G_hWnd, nCmdShow);    
	UpdateWindow(G_hWnd);            

	return (TRUE);                 
}
//=============================================================================
int EventLoop()
{
 static unsigned short _usCnt = 0; 
 register MSG msg;

	while( 1 ) {
		if( PeekMessage( &msg, NULL, 0, 0, PM_NOREMOVE ) ) {
			if( !GetMessage( &msg, NULL, 0, 0 ) ) {
				return msg.wParam;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			UpdateScreen();
		}
		else WaitMessage();
	}
}
//=============================================================================
void Initialize()
{

	if (_InitWinsock() == FALSE) {
		MessageBox(G_hWnd, "Socket 1.1 not found! Cannot execute program.","ERROR", MB_ICONEXCLAMATION | MB_OK);
		PostQuitMessage(0);
		return;
	}

	g_game = new class CGame(G_hWnd);
	if (g_game->bInit() == FALSE) {
		PutLogList("(!!!) STOPPED!");
		return;
	}

	SetPriorityClass( GetCurrentProcess(), ABOVE_NORMAL_PRIORITY_CLASS );

	G_mmTimer = _StartTimer(TICKDELAY);

	G_pListenSock = new class XSocket(G_hWnd, SERVERSOCKETBLOCKLIMIT);
	G_pListenSock->bListen(g_game->m_cGameServerAddr, g_game->m_iGameServerPort, WM_USER_ACCEPT);


	G_sLogCounter = 0 ;
	ZeroMemory(G_cLogBuffer, sizeof(G_cLogBuffer));
}
//=============================================================================
void OnDestroy()
{
	if (G_pListenSock != NULL) delete G_pListenSock;
	if (G_pLogSock != NULL) delete G_pLogSock;

	if (g_game != NULL) {
		g_game->Quit();
	delete g_game;
	}

	if (G_mmTimer != NULL) _StopTimer(G_mmTimer);
	_TermWinsock();

	PostQuitMessage(0);
}
//=============================================================================
void UpdateScreen()
{
	if (G_cMsgUpdated == TRUE) {
		InvalidateRect(G_hWnd, NULL, TRUE);
		G_cMsgUpdated = FALSE;
	}
}
//=============================================================================
void OnPaint()
{
 HDC hdc;
 PAINTSTRUCT ps;
 register short i;
 char CurMsg;

	hdc = BeginPaint(G_hWnd, &ps);

        FillRect(hdc, &rctSrvList, (HBRUSH)(7));
        SelectObject(hdc, GetStockObject(ANSI_VAR_FONT));
	SetBkMode(hdc,TRANSPARENT);

	CurMsg = LogMsg.CurMsg;
        for (i = 0; i <= MAXLOGSTOSHOW; i++)
            {
             if(CurMsg < 0) CurMsg = (MAXLOGMSGS-1);
	     if (strlen(LogMsg.Message[CurMsg]) != NULL)
                {
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

	if (g_game	!= NULL)
		g_game->DisplayInfo(hdc);

	EndPaint(G_hWnd, &ps);
}
//=============================================================================
void  OnKeyUp(WPARAM wParam, LPARAM lParam)
{
}
//=============================================================================
void OnAccept()
{
	g_game->bAccept(G_pListenSock);
}
//=============================================================================
void CALLBACK _TimerFunc(UINT wID, UINT wUser, DWORD dwUSer, DWORD dw1, DWORD dw2)
{
	PostMessage(G_hWnd, WM_USER_TIMERSIGNAL, wID, NULL);
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
void PutLogFileList(const char * cStr, char *FileName)
{
 FILE * pFile;
 char cBuffer[MAXLOGLINESIZE+100];
 SYSTEMTIME SysTime;

        _mkdir("Logs");
		if(strlen(cStr) > MAXLOGLINESIZE) return;
        if(FileName == NULL) pFile = fopen(EVENT_LOGFILE, "at");
        else if(IsSame(FileName, XSOCKET_LOGFILE)) pFile = fopen(FileName, "ab");
		else pFile = fopen(FileName, "at");
	if (pFile == NULL) return;

	ZeroMemory(cBuffer, sizeof(cBuffer));

	GetLocalTime(&SysTime);
	wsprintf(cBuffer, "(%4d:%2d:%2d:%2d:%2d) - ", SysTime.wYear, SysTime.wMonth, SysTime.wDay, SysTime.wHour, SysTime.wMinute);
	strcat(cBuffer, cStr);
	strcat(cBuffer, "\n");

	fwrite(cBuffer, 1, strlen(cBuffer), pFile);
	fclose(pFile);
}

void Assertion(const char * assertion, const char * file, const uint32 line)
{
	char buffer[MAXLOGLINESIZE+100];

	sprintf(buffer, "%s(%i)(%d.%d): ASSERTION FAILED:  %s", file, line,
		UPPER_VERSION, LOWER_VERSION, assertion); 
	PutLogFileList((const char*)buffer, DEBUG_LOGFILE);
}
//=============================================================================
/*void PutLogList(char * cMsg, BYTE MsgLvl, bool PutOnFile, char *FileName)
{
        if(strlen(cMsg) <= MAXLOGMSGSIZE)
          {
           G_cMsgUpdated = TRUE;
           LogMsg.CurMsg++;
           if(LogMsg.CurMsg >= MAXLOGMSGS) LogMsg.CurMsg = 0;
           ZeroMemory(LogMsg.Message[LogMsg.CurMsg], sizeof(LogMsg.Message[LogMsg.CurMsg]));
           SafeCopy(LogMsg.Message[LogMsg.CurMsg], cMsg);
           LogMsg.MsgLvl[LogMsg.CurMsg] = MsgLvl;
           UpdateScreen();
          }
        else if(strlen(cMsg) > MAXLOGLINESIZE) return;
        if(PutOnFile == TRUE) PutLogFileList(cMsg, FileName);
}*/
void PutLogList(const char * cMsg)
{

	G_cMsgUpdated = TRUE;
	PutLogFileList(cMsg, ADMIN_LOGFILE);
	SendMessage(List1,(UINT)LB_ADDSTRING,(WPARAM)0,(LPARAM)cMsg);
	if(scrolling)
		SendMessage(List1,(UINT)LB_SETCURSEL,ItemCount,0);
		ItemCount++;

}
void PutLogList(const string msg)
{
	PutLogList(msg.c_str());
}
void LogError(const char * cMsg)
{
	PutLogList("");
	PutLogList(cMsg);
	PutLogList("");
}
void LogError(const string msg)
{
	LogError(msg.c_str());
}
//=============================================================================
BYTE bGetOffsetValue(char * cp, DWORD offset)
{
 char   *pcp;
 BYTE	*bp;

 pcp = (char *)cp;
 pcp += offset;
 bp = (BYTE *)pcp;
 return *bp;
}
//=============================================================================
WORD wGetOffsetValue(char * cp, DWORD offset)
{
 char   *pcp;
 WORD	*wp;

 pcp = (char *)cp;
 pcp += offset;
 wp = (WORD *)pcp;
 return *wp;
}
//=============================================================================
DWORD dwGetOffsetValue(char * cp, DWORD offset)
{
	char   *pcp;
	DWORD	*dwp;

	pcp = (char *)cp;
	pcp += offset;
	dwp = (DWORD *)pcp;
	return *dwp;
}

uint64 ullGetOffsetValue(char * cp, DWORD offset)
{
	char   *pcp;
	uint64	*dwp;

	pcp = (char *)cp;
	pcp += offset;
	dwp = (uint64 *)pcp;
	return *dwp;
}
//=============================================================================
void PutOffsetValue(char * cp, DWORD offset, BYTE size, uint64 value)
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
 register DWORD dw;
	 
		if(lenght == 0){
			dw = 0;
			if(c2[dw] == NULL) return;
			while(c2[dw] != NULL){
				c1[dw] = c2[dw];
				dw++;
			}
		}
		else for(dw = 0; dw < lenght; dw++) c1[dw] = c2[dw];

		c1[dw] = NULL;
}
//=============================================================================
bool IsSame(char *c1, char *c2)
{
 DWORD size1, size2;
 
		size1 = strlen(c1);
		size2 = strlen(c2);
		if(size1 == size2 && memcmp(c1, c2, size1) == 0) return true;
        else return false;
}
//=============================================================================

HWND BCX_Listbox(char* Text,HWND hWnd,int id,int X,int Y,int W,int H,int Style,int Exstyle)
{
	HWND  A;
	if (!Style)
	{
		Style = WS_VSCROLL | WS_VISIBLE | WS_CHILD | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | LBS_NOTIFY | WS_TABSTOP;
	}
	if (Exstyle == -1)
	{
		Exstyle=WS_EX_CLIENTEDGE;
	}
	A = CreateWindowEx(Exstyle,"Listbox",NULL,Style,
		X*BCX_ScaleX, Y*BCX_ScaleY, W*BCX_ScaleX, H*BCX_ScaleY,
		hWnd,(HMENU)id,BCX_hInstance,NULL);
	SendMessage(A,(UINT)WM_SETFONT,(WPARAM)GetStockObject
		(DEFAULT_GUI_FONT),(LPARAM)MAKELPARAM(FALSE,0));
	return A;
}

HWND BCX_Editbox(char* Text,HWND hWnd,int id,int X,int Y,int W,int H,int Style,int Exstyle)
{
	HWND  A;
	if (!Style)
	{
		Style = WS_VISIBLE | WS_CHILD | LBS_HASSTRINGS | LBS_NOINTEGRALHEIGHT | WS_TABSTOP;
	}
	if (Exstyle == -1)
	{
		Exstyle=WS_EX_CLIENTEDGE;
	}
	A = CreateWindowEx(Exstyle,"EDIT",NULL,Style,
		X*BCX_ScaleX, Y*BCX_ScaleY, W*BCX_ScaleX, H*BCX_ScaleY,
		hWnd,(HMENU)id,BCX_hInstance,NULL);
	SendMessage(A,(UINT)WM_SETFONT,(WPARAM)GetStockObject
		(DEFAULT_GUI_FONT),(LPARAM)MAKELPARAM(FALSE,0));
	return A;
}

HWND BCX_Button(char* Text,HWND hWnd,int id,int X,int Y,int W,int H,int Style,int Exstyle)
{
	HWND  A;
	if (!Style)
	{
		Style = WS_CHILD | WS_VISIBLE | WS_BORDER;
	}
	A = CreateWindowEx(0,"Button",Text,Style,
		X*BCX_ScaleX, Y*BCX_ScaleY, W*BCX_ScaleX, H*BCX_ScaleY,
		hWnd,(HMENU)id,BCX_hInstance,NULL);
	SendMessage(A,(UINT)WM_SETFONT,(WPARAM)GetStockObject
		(DEFAULT_GUI_FONT),(LPARAM)MAKELPARAM(FALSE,0));
	return A;
}

void parseCommand(char* pMsg)
{
	if (pMsg == NULL) return;

	char   seps[] = "= \t\n";
	char   * token, * token2;
	class  CStrTok * pStrTok;
	char * cName[11];
	char buff[100];
	BOOL bFlag;
	int i;
	pStrTok = new class CStrTok(pMsg, seps);
	token = pStrTok->pGet();
	token2 = pStrTok->pGet();
	bFlag = false;
	/*	if (memcmp(pMsg,"ascii ",5) == 0) {
	//if (strlen(token) == 1) {
	bFlag = TRUE;
	char znak[1];
	memcpy(znak,token,1);
	wsprintf(buff,"AscII%d/%s.txt",znak[0],token);
	PutLogList(buff);
	}*/

	if (memcmp(pMsg,"check ",6) == 0) {
		if(!g_clientList)
		{
			PutLogList("No client list! Server is probably off.");
			return;
		}

		if (token2 != NULL) {
			ZeroMemory(cName, sizeof(cName));
			memcpy(cName, token2,11);
		} 


		if (cName != NULL) {

			for (i = 1; i < MAXCLIENTS; i++)
				if ((g_clientList[i] != NULL) && (memcmp(g_clientList[i]->m_cCharName, cName, 10) == 0)) {
					ZeroMemory(buff, sizeof(buff));
					if ((g_clientList[i] != NULL) && (memcmp(g_clientList[i]->m_cCharName, cName, 10) == 0)) {
						wsprintf(buff, "%s:    Str:%d  Dex:%d  Vit:%d  Int:%d  Mag:%d  Chr:%d    Map:%s - %i , %i    Admin level:%i", g_clientList[i]->m_cCharName, g_clientList[i]->GetStr(),  g_clientList[i]->GetDex(), g_clientList[i]->m_iVit, g_clientList[i]->GetInt(),g_clientList[i]->GetMag(), g_clientList[i]->m_iRange, g_clientList[i]->m_cMapName, g_clientList[i]->m_sX, g_clientList[i]->m_sY, g_clientList[i]->m_iAdminUserLevel);
						PutLogList(buff);
					}else{
						wsprintf(buff,"Player %s is offline.", cName);
						PutLogList(buff);
					}
				}
		}
	}
	/*
	if (memcmp(pMsg,"start apocalypse",16) == 0) {
	if(!g_game)
	{
	PutLogList("Couldn't get the game server pointer! Server is probably off.");
	return;
	}
	g_game->GlobalStartApocalypseMode();
	}

	if (memcmp(pMsg,"end apocalypse",14) == 0) {
	if(!g_game)
	{
	PutLogList("Couldn't get the game server pointer! Server is probably off.");
	return;
	}
	g_game->GlobalEndApocalypseMode();
	}
	*/

	else if (memcmp(pMsg,"start heldenian",15) == 0) {
		if(!g_game)
		{
			PutLogList("Couldn't get the game server pointer! Server is probably off.");
			return;
		}
		g_game->StartHeldenianMode();
	}
	else if (memcmp(pMsg,"end heldenian 1",15) == 0) {
		if(!g_game)
		{
			PutLogList("Couldn't get the game server pointer! Server is probably off.");
			return;
		}
		g_game->HeldenianEndWarNow(g_game->m_iHeldenianType, ARESDEN); 
	}
	else if (memcmp(pMsg,"end heldenian 2",15) == 0) {
		if(!g_game)
		{
			PutLogList("Couldn't get the game server pointer! Server is probably off.");
			return;
		}
		g_game->HeldenianEndWarNow(g_game->m_iHeldenianType, ELVINE); 
	}
	else if (memcmp(pMsg,"start crusade",13) == 0) {
		if(!g_game)
		{
			PutLogList("Couldn't get the game server pointer! Server is probably off.");
			return;
		}
		g_game->GlobalStartCrusadeMode();
	}else if (memcmp(pMsg,"end crusade",11) == 0) {
		if(!g_game)
		{
			PutLogList("Couldn't get the game server pointer! Server is probably off.");
			return;
		}
		g_game->ManualEndCrusadeMode(0);
	}else if (memcmp(pMsg,"benchmark",9) == 0) {
		if(!g_game)
		{
			PutLogList("Couldn't get the game server pointer! Server is probably off.");
			return;
		}

		int ix = 60, iy = 60;
		Unit * owner;
		Point p;
		p.x = p.y = 60;

		CMap * map = g_game->m_pMapList[1];

		DWORD time;
		time = timeGetTime();
		uint32 count = 0;
		for(uint32 i=0; i < 100000000; i++)
		{
			count += map->bGetIsMoveAllowedTile(p);
		}

		char txt[50];
		ZeroMemory(txt, sizeof(txt));

		wsprintf(txt, "time: %u, %u", timeGetTime() - time, count);
		PutLogList(txt);
	}
	else if (memcmp(pMsg,"broadcast ",10) == 0) {
		if(!g_clientList)
		{
			PutLogList("No client list! Server is probably off.");
			return;
		}
		if(!g_game)
		{
			PutLogList("Couldn't get the game server pointer! Server is probably off.");
			return;
		}
		//tLogList(token2);
		char ss[100];
		ZeroMemory(ss,100);
		memcpy(ss,pMsg,strlen(pMsg));
		ss[0]=' ';
		ss[1]=' ';
		ss[2]=' ';
		ss[3]=' ';
		ss[4]=' ';
		ss[5]=' '; 
		ss[6]=' ';
		ss[7]=' ';
		ss[8]=' ';
		ss[9]=' ';
		int i;
		char*p=ss;
		while(isspace(*p) && (*p))p++;
		memmove(ss,p,strlen(p)+1);
		wsprintf(ss,"%s",ss);
		int do_ilu;
		do_ilu=0;
		// Send to clients on current HG
		for (i = 1; i < MAXCLIENTS; i++) {
			if (g_clientList[i] != NULL) {
				g_game->ShowClientMsg(i,ss);
				do_ilu++;
			}
		}

		// Send to all other HGs through Login Server
		if (strlen(ss) < 90) {
			char * cp2;
			WORD * wp;
			char * pkt = new char[strlen(ss) + 20];
			ZeroMemory(pkt, strlen(ss) + 20);
			cp2 = (char *)pkt;
			*cp2 = GSM_CHATMSG;
			cp2++;
			*cp2 = CHAT_GM;
			cp2++;
			//ip = (int *)cp2;
			//*ip = NULL;
			cp2 += 4;
			strcpy(cp2, "Server");
			cp2 += 10;
			wp  = (WORD *)cp2;
			*wp = (WORD)strlen(ss);
			cp2 += 2;
			strcpy(cp2, ss);
			cp2 += strlen(ss);
			g_game->bStockMsgToGateServer(pkt, strlen(ss) + 18);
		}

		char buff[100];
		wsprintf(buff,"(!) The Message '%s' was sent to all players ( %d )",ss,do_ilu);
		PutLogList(buff);
	}else if(memcmp(pMsg, "maplist", 7) == 0){
		if(!g_mapList) return;

		for (i = 0; i < MAXMAPS; i++)
			if (g_mapList[i] != NULL) {
				wsprintf(buff, "[%d] %s", g_mapList[i]->m_iTotalActiveObject, g_mapList[i]->m_cName);
				PutLogList(buff);
			}
	}else if(memcmp(pMsg, "clientlist", 10) == 0){
		if(!g_clientList) return;

		for (i = 0; i < MAXCLIENTS; i++)
			if (g_clientList[i] != NULL) {
				wsprintf(buff, "Char:%s(%d) %d on %s (%s)", g_clientList[i]->m_cCharName, 
					g_clientList[i]->m_iLevel,
					g_clientList[i]->m_side,
					g_clientList[i]->m_cAccountName,
					g_clientList[i]->m_cIPaddress);
				PutLogList(buff);
			}
	}else{
		wsprintf(buff,"(!!!) %s - unrecognized commad",pMsg);
		PutLogList(buff);
	}

}
