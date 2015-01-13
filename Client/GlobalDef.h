#ifndef GLOBALDEF_H
#define GLOBALDEF_H

#define NAME_WORLDNAME1			"WS1" // Name for default (1st) server
#define MSG_WORLDNAME1			"180/200 Low-Rate Server" // Long name for 1st server...
#define NAME_WORLDNAME2			"WS2"
#define MSG_WORLDNAME2			"High-Rate Server"
#define MSG_HOMEPAGE			"http://www.helbreathlegion.net/"

//#define SERVER_IP			"74.55.185.122"	// dedi
//#define SERVER_IP			"65.175.174.30" //test-Server
//#define SERVER_IP			"192.168.1.11"
#define SERVER_IP			"192.168.1.4"
#define SERVER_PORT			321

#define LANG	ENGLISH
//#define LANG	SPANISH

/*** Some more compilation options ***/
//#define USING_WIN_IME		// Used for unicode characters (unchecked)
#define MAKE_ACCOUNT		// Enable acc creation. Missing sprites, fixed!
#define SELECTSERVER		// Show/Hides server selection screen.

#define COMMA_GOLD		// Allows to show commas number (ie: 1,200,000)

//#define DEF_HTMLCOMMOM

//#define  _DEBUG				// Multi-Client, Instant-logout, Version check, Badwords,
								// Mics debug msgs, CtrlQ for admins, Show status, Cursor position

#ifdef _DEBUG
	#define SPEEDHAX_RUN	1.5
	#define SPEEDHAX_ATK 2
	#define SPEEDHAX_HIT	3
	#define LOGINCFG
	#define _SCDEBUG
	#define WINDOWED_MODE	// Shows HB in a windowed mode (for debug purpose only, sprite will bug....)
#else
	#define SPEEDHAX_RUN	1
	#define SPEEDHAX_ATK 1
	#define SPEEDHAX_HIT	1
#define LOGINCFG
#endif
		
#endif