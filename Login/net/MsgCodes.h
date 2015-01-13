#ifndef _MSGCODES_H_
#define _MSGCODES_H_

//Socket-related messages
#define WM_USER_STARTGAMESIGNAL	                            WM_USER + 10
#define WM_USER_ACCEPT		                                WM_USER + 100
#define WM_GATESERVER_ACCEPT		                        WM_USER + 101
#define WM_ONGAMESERVERSOCKETEVENT                          WM_USER + 1000
#define WM_ONCLIENTSOCKETEVENT	                            WM_ONGAMESERVERSOCKETEVENT + MAXGAMESERVERSOCKETS + 10

#include "..\..\shared\NetMessages.h"

#endif




