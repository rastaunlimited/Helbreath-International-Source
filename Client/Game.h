// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GAME_H__0089D9E3_74E6_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_GAME_H__0089D9E3_74E6_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <windowsx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <mmsystem.h> 
#include <winbase.h>
#include <cstring>
#include <vector>

#include <process.h>
#include <direct.h>
#include <set>

#include "..\shared\common.h"
#include "..\shared\NetMessages.h"
#include "..\shared\items.h"
#include "..\shared\npcType.h"

#include "GlobalDef.h"
#include "directx\DXC_ddraw.h"
#include "directx\DXC_dinput.h"
#include "directx\DSound.h"
#include "directx\SoundBuffer.h"
#include "directx\YWSound.h"
#include "net\XSocket.h"
#include "directx\Sprite.h"
#include "directx\SpriteID.h"
#include "Misc.h"
#include "StrTok.h"
#include "net\Msg.h"
#include "directx\Effect.h"
#include "map\MapData.h"
#include "char\ActionID.h"
#include "ui\MouseInterface.h"
#include "char\CharInfo.h"
#include "char\item\Item.h"
#include "char\Magic.h"
#include "char\Skill.h"
#include "char\DynamicObjectID.h"
#include "char\item\BuildItem.h"
#include "char\item\ItemName.h"
#include "char\Curse.h"

#ifdef USING_WIN_IME
	#include <RICHEDIT.H>
#endif

//v2.18
#define BTNSZX				74
#define BTNSZY				20
#define LBTNPOSX			30
#define RBTNPOSX			154
#define BTNPOSY				292

#define INDEX4_MSGID		0
#define INDEX2_MSGTYPE		4

#define SOCKETBLOCKLIMIT	300

#define MAXSPRITES			25000	// 20000 // Snoopy: Adjusted!
#define MAXTILES			1000	// 800 // Snoopy: Adjusted!
#define MAXEFFECTSPR		300
#define MAXSOUNDEFFECTS		200		// 110   //Snoopy: Adjusted!
#define MAXCHATMSGS			500
#define MAXWHISPERMSG		5
#define MAXCHATSCROLLMSGS	80
#define MAXEFFECTS			300	//600 <- original
#define CHATTIMEOUT_A		4000
#define CHATTIMEOUT_B		500
#define CHATTIMEOUT_C		2000
#define MAXITEMS			50
#define MAXBANKITEMS		120 
#define MAXGUILDSMAN		32
#define MAXMENUITEMS		140  //v2.15  120 ->140
#define TEXTDLGMAXLINES		300 //v2.18 3000->300

#define MAXMAGICTYPE		100
#define MAXSKILLTYPE		10
#define MAXWHETHEROBJECTS	600
#define MAXBUILDITEMS		100
#define MAXGAMEMSGS			300
#define MAXITEMNAMES		1000
#define MAXGUILDNAMES		100
#define MAXSELLLIST			12

#define WM_USER_GAMESOCKETEVENT	WM_USER + 2000
#define WM_USER_LOGSOCKETEVENT	WM_USER + 2001

#define GAMEMODE_NULL					-2
#define GAMEMODE_ONQUIT					-1
#define GAMEMODE_ONMAINMENU				0
#define GAMEMODE_ONCONNECTING			1
#define GAMEMODE_ONLOADING				2
#define GAMEMODE_ONWAITINGINITDATA		3
#define GAMEMODE_ONMAINGAME				4
#define GAMEMODE_ONCONNECTIONLOST		5
#define GAMEMODE_ONMSG					6
#define GAMEMODE_ONCREATENEWACCOUNT		7
#define GAMEMODE_ONLOGIN				8
#define GAMEMODE_ONQUERYFORCELOGIN		9
#define GAMEMODE_ONSELECTCHARACTER		10
#define GAMEMODE_ONCREATENEWCHARACTER	11
#define GAMEMODE_ONWAITINGRESPONSE		12
#define GAMEMODE_ONQUERYDELETECHARACTER 13
#define GAMEMODE_ONLOGRESMSG			14
#define GAMEMODE_ONCHANGEPASSWORD		15
#define GAMEMODE_ONVERSIONNOTMATCH		17
#define GAMEMODE_ONINTRODUCTION			18
#define GAMEMODE_ONAGREEMENT			19
#define GAMEMODE_ONSELECTSERVER			20
#define GAMEMODE_ONINPUTKEYCODE			21

#define SERVERTYPE_GAME			1
#define SERVERTYPE_LOG			2

#define CURSORSTATUS_NULL		0
#define CURSORSTATUS_PRESSED	1
#define CURSORSTATUS_SELECTED	2
#define CURSORSTATUS_DRAGGING	3

#define SELECTEDOBJTYPE_DLGBOX	1
#define SELECTEDOBJTYPE_ITEM	2

#define DOUBLECLICKTIME			300
#define MAXCRUSADESTRUCTURES	300

#define NONE						-1
#define STAT_STR					0
#define STAT_VIT					1
#define STAT_DEX					2
#define STAT_INT					3
#define STAT_MAG					4
#define STAT_CHR					5


class CGame
{
public:
	void DrawPartyStats(int ix, int iy, int iFrame);
	void Notify_PartyInfo(char * Data);
	void DrawPartyStats();

	void NotifyMsg_Heldenian(char * Data);
	void DrawHeldenianStats();
	void TimeStamp(char * pString);
	BOOL m_bHappyHour;
	void DrawQuestHelper();
	void LoadFriendList();
	void SaveFriendList();
	void DrawDialogBox_FriendList(short msX, short msY);
	void DlgBoxClick_FriendList(short msX, short msY);

	DWORD lastScreenUpdate;

	int m_iTotalFriends;
	int m_iFriendIndex;
	DWORD lastFriendUpdate;
	struct {
		bool online;
		char friendName[13];
		bool updated;
	} friendsList[13];

	// CLEROTH - AURAS
	void CheckActiveAura(short sX, short sY, DWORD dwTime, short sOwnerType);
	void CheckActiveAura2(short sX, short sY, DWORD dwTime, short sOwnerType);

	// MJ Stats Change Related functions - Alastor
	void DrawDialogBox_ChangeStatsMajestic(short msX, short msY);		// Change stats using majestic - Alastor
	void DlgBoxClick_ChangeStatsMajestic(short msX, short msY);			// Change stats using majestic - Alastor

	// MJ Stats Change Related vars - Alastor
	char cStateChange1;
	char cStateChange2;
	char cStateChange3;

	int m_iTeleportMapCount;
	void ResponseTeleportList(char * Data);
	void ResponseChargedTeleport(char * Data);
	void * operator new (size_t size)
	{
		return HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, size);
	};

	void operator delete(void * mem)
	{
		HeapFree(GetProcessHeap(), HEAP_NO_SERIALIZE, mem);
	};

	void ItemEquipHandler(char cItemID);
	void ReleaseEquipHandler(char cEquipPos);

	void ReadSettings();
	uint32 ReadSettingsVar(const char * var);
	void WriteSettings();
	void WriteSettingsVar(const char * var, uint32 val);

	int  iGetManaCost(int iMagicNo);
	void UseMagic(int iMagicNo);
	BOOL _bCheckMoveable( short sx, short sy );
	BOOL FindGuildName(char* pName, int* ipIndex);
	void bItemDrop_SkillDialog();
	void bItemDrop_IconPannel(short msX, short msY);
	void bItemDrop_Character();
	void bItemDrop_Inventory(short msX, short msY);
	void bItemDrop_ItemUpgrade();
	void bItemDrop_SellList(short msX, short msY);
	void bItemDrop_ExchangeDialog(short msX, short msY);
	void bItemDrop_Bank(short msX, short msY);
	void bItemDrop_ExternalScreen(char cItemID, short msX, short msY);
	void CreateScreenShot();
	void CrusadeWarResult(int iWinnerSide);
	void CrusadeContributionResult(int iWarContribution);
	void CannotConstruct(int iCode);
	void DrawTopMsg();
	void SetTopMsg(const char * pString, unsigned char iLastSec);
	void DrawAstoriaStats();
	void DrawObjectFOE(int ix, int iy, int iFrame);
	void GrandMagicResult(char * pMapName, int iV1, int iV2, int iV3, int iV4, int iHP1, int iHP2, int iHP3, int iHP4) ;
	void MeteorStrikeComing(int iCode);
	void _Draw_OnLogin(char * pAccount, char * pPassword, int msX, int msY, int iFrame = 60000);
	void DrawNewDialogBox(char cType, int sX, int sY, int iFrame, BOOL bIsNoColorKey = FALSE, BOOL bIsTrans = FALSE);
	void AddMapStatusInfo(char * Data, BOOL bIsLastData);
	void _RequestMapStatus(char * pMapName, int iMode);
	int  GetCharKind(char *str, int index);
	void ReceiveString(char * pString);
	void EndInputString();
	void ClearInputString();
	void ShowReceivedString(BOOL bIsHide = FALSE);
		bool GetText(HWND hWnd,UINT msg,WPARAM wparam, LPARAM lparam);
	BOOL bReadItemNameConfigFile();
	void DrawDialogBoxs(short msX, short msY, short msZ, char cLB);
	void DrawDialogBox_Character(short msX, short msY);//1
	void DrawDialogBox_Inventory(int msX, int msY);//2
	void DrawDialogBox_Magic(short msX, short msY, short msZ);//3
	void DrawDialogBox_GuildMenu(short msX, short msY);//7
	void DrawDialogBox_GuildOperation(short msX, short msY);//8
	void DrawDialogBox_GuideMap(short msX, short msY, char cLB);//9
	void DrawDialogBox_Chat(short msX, short msY, short msZ, char cLB);//10
	void DrawDialogBox_Shop(short msX, short msY, short msZ, char cLB);//11
	void DrawDialogBox_LevelUpSetting(short msX, short msY);//12
	void DrawDialogBox_CityHallMenu(short msX, short msY);//13
	void DrawDialogBox_Bank(short msX, short msY, short msZ, char cLB);//14
	void DrawDialogBox_Skill(short msX, short msY, short msZ, char cLB);//15
	void DrawDialogBox_MagicShop(short msX, short msY, short msZ);//16
	void DrawDialogBox_QueryDropItemAmount();//17
	void DrawDialogBox_Text(short msX, short msY, short msZ, char cLB);//18
	void DrawDialogBox_SysMenu(short msX, short msY, char cLB);//19
	void DrawDialogBox_NpcActionQuery(short msX, short msY);//20
	void DrawDialogBox_NpcTalk(short msX, short msY, char cLB);//21
	void DrawDialogBox_Map();//22
	void DrawDialogBox_SellorRepairItem(short msX, short msY);//23
	void DrawDialogBox_Fishing(short msX, short msY);//24
	void DrawDialogBox_ShutDownMsg(short msX, short msY);//25
	void DrawDialogBox_SkillDlg(short msX, short msY, short msZ, char cLB);//26
	void DrawDialogBox_Exchange(short msX, short msY);//27
	void DrawDialogBox_Quest(int msX, int msY);//28
	void DrawDialogBox_GaugePannel();//29
	void DrawDialogBox_IconPannel(short msX, short msY);//30
	void DrawDialogBox_SellList(short msX, short msY);//31
	void DrawDialogBox_Party(short msX, short msY, short msZ, char cLB);//32
	void DrawDialogBox_CrusadeJob(short msX, short msY);//33
	void DrawDialogBox_ItemUpgrade(int msX, int msY);//34
	void DrawDialogBox_Help(int msX, int msY);//35
	void DrawDialogBox_Commander(int msX, int msY);//36
	void DrawDialogBox_Constructor(int msX, int msY);//37
	void DrawDialogBox_Soldier(int msX, int msY);//38
    void DrawDialogBox_ItemDrop(short msX, short msY);//4
	void DrawDialogBox_WarningMsg(short msX, short msY);//6
	void DrawDialogBox_15AgeMsg(short msX, short msY);//5
	void DrawDialogBox_FeedBackCard(short msX, short msY);//40
	void DisplayCommaNumber_G_cTxt(int iGold);// Name changed by Snoopy (easyer to understand...)

	void DrawDialogBox_ConfirmExchange(short msX, short msY); //41

	void DrawDialogBox_DKMenuArmor(int msX, int msY); // 52
	void DlgBoxClick_DKMenuArmor(int msX, int msY);

	void DrawDialogBox_DKMenuWeapons(int msX, int msY); // 53
	void DlgBoxClick_DKMenuWeapons(int msX, int msY);

	// Slates - Alastor
	void bItemDrop_Slates();
	void DlgBoxClick_Slates(short msX, short msY);
	void DrawDialogBox_Slates(short msX, short msY, short msZ, char cLB);//40

	BOOL _bCheckDlgBoxClick(short msX, short msY);
	void DlgBoxClick_WarningMsg(short msX, short msY);
	void DlgBoxClick_15AgeMsg(short msX, short msY);
	void DlgBoxClick_ItemDrop(short msX, short msY);
	void DlgBoxClick_Character(short msX, short msY);
	void DlgBoxClick_Inventory(short msX, short msY);
	void DlgBoxClick_Magic(short msX, short msY);
	void DlgBoxClick_GuildMenu(short msX, short msY);
	void DlgBoxClick_GuildOp(short msX, short msY);
	void DlgBoxClick_GuideMap(short msX, short msY);
	void DlgBoxClick_Shop(short msX, short msY);
	void DlgBoxClick_LevelUpSettings(short msX, short msY);
	void DlgBoxClick_CityhallMenu(short msX, short msY);
	void DlgBoxClick_Bank(short msX, short msY);
	void DlgBoxClick_Skill(short msX, short msY);
	void DlgBoxClick_MagicShop(short msX, short msY);
	void DlgBoxClick_FeedBackCard(short msX, short msY);
	void DlgBoxClick_Text(short msX, short msY);
	void DlgBoxClick_SysMenu(short msX, short msY);
	void DlgBoxClick_NpcActionQuery(short msX, short msY);
	void DlgBoxClick_NpcTalk(int msX, int msY);
	void DlgBoxClick_ItemSellorRepair(short msX, short msY);
	void DlgBoxClick_Fish(short msX, short msY);
	void DlgBoxClick_ShutDownMsg(short msX, short msY);
	void DlgBoxClick_SkillDlg(short msX, short msY);
	void DlgBoxClick_Exchange(short msX, short msY);

	void DlgBoxClick_Quest(int msX, int msY);
	void DlgBoxClick_SellList(short msX, short msY);
	void DlgBoxClick_IconPannel(short msX, short msY);
	void DlgBoxClick_Party(short msX, short msY);
	void DlgBoxClick_CrusadeJob(short msX, short msY);
	void DlgBoxClick_ItemUpgrade(int msX, int msY);
	void DlgBoxClick_Help(int msX, int msY);
	void DlgBoxClick_Commander(int msX, int msY);
	void DlgBoxClick_Constructor(int msX, int msY);
	void DlgBoxClick_Soldier(int msX, int msY);
	void NotifyMsgHandler(char * Data);
	void NotifyMsg_GlobalAttackMode(char * Data);
	void NotifyMsg_QuestReward(char * Data);
	void NotifyMsg_QuestContents(char * Data);
	void NotifyMsg_ItemColorChange(char * Data);
	void NotifyMsg_DropItemFin_CountChanged(char * Data);
	void NotifyMsg_CannotGiveItem(char * Data);
	void NotifyMsg_GiveItemFin_CountChanged(char * Data);
	void NotifyMsg_SetExchangeItem(char * Data);
	void NotifyMsg_OpenExchageWindow(char * Data);
	void NotifyMsg_DownSkillIndexSet(char * Data);
	void NotifyMsg_AdminInfo(char * Data);
	void NotifyMsg_WhetherChange(char * Data);
	void NotifyMsg_FishChance(char * Data);
	void NotifyMsg_EventFishMode(char * Data);
	void NotifyMsg_NoticeMsg(char * Data);
	void NotifyMsg_RatingPlayer(char * Data);
	void NotifyMsg_CannotRating(char * Data);
	void NotifyMsg_PlayerShutUp(char * Data);
	void NotifyMsg_TimeChange(char * Data);
	void NotifyMsg_Hunger(char * Data);
	void NotifyMsg_PlayerProfile(char * Data);
	void NotifyMsg_WhisperMode(BOOL bActive, char * Data);
	void NotifyMsg_PlayerStatus(BOOL bOnGame, char * Data);
	void NotifyMsg_Range(char * Data);
	void NotifyMsg_ItemRepaired(char * Data);
	void NotifyMsg_RepairItemPrice(char * Data);
	void NotifyMsg_CannotRepairItem(char * Data);
	void NotifyMsg_CannotSellItem(char * Data);
	void NotifyMsg_SellItemPrice(char * Data);
	void NotifyMsg_ShowMap(char * Data);
	void NotifyMsg_SkillUsingEnd(char * Data);
	void NotifyMsg_TotalUsers(char * Data);
	void NotifyMsg_EventStart(char * Data);
	void NotifyMsg_EventStarting(char * Data);
	void NotifyMsg_Casualties(char * Data);	
	void NotifyMsg_RelicInAltar(char * Data);
	void NotifyMsg_RelicGrabbed(char * Data);
	void NotifyMsg_CTRWinner(char * Data);
	void NotifyMsg_MagicEffectOff(char * Data);
	void NotifyMsg_MagicEffectOn(char * Data);
	void NotifyMsg_SetItemCount(char * Data);
	void NotifyMsg_ItemDepleted_EraseItem(char * Data);
	void NotifyMsg_ServerChange(char * Data);
	void NotifyMsg_Skill(char * Data);
	void NotifyMsg_DropItemFin_EraseItem(char * Data);
	void NotifyMsg_GiveItemFin_EraseItem(char * Data);
	void NotifyMsg_EnemyKillReward(char * Data);
	void NotifyMsg_PKcaptured(char * Data);
	void NotifyMsg_PKpenalty(char * Data);
	void NotifyMsg_ItemToBank(char * Data);
	void NotifyMsg_ItemLifeSpanEnd(char * Data);
	void NotifyMsg_ItemReleased(char * Data);
	void NotifyMsg_LevelUp(char * Data);
	void NotifyMsg_SettingSuccess(char * Data); // CLEROTH - LU
	void NotifyMsg_MP(char * Data);
	void NotifyMsg_SP(char * Data);
	void NotifyMsg_SkillTrainSuccess(char * Data);
	void NotifyMsg_MagicStudyFail(char * Data);
	void NotifyMsg_MagicStudySuccess(char * Data);
	void NotifyMsg_DismissGuildsMan(char * Data);
	void NotifyMsg_NewGuildsMan(char * Data);
	void NotifyMsg_CannotJoinMoreGuildsMan(char * Data);
	void NotifyMsg_GuildDisbanded(char * Data);
	void NotifyMsg_Exp(char * Data);
	void NotifyMsg_Killed(char * Data);
	void NotifyMsg_HP(char * Data);
	void NotifyMsg_ItemPurchased(char * Data);
	void NotifyMsg_DismissGuildReject(char * Data);
	void NotifyMsg_DismissGuildApprove(char * Data);
	void NotifyMsg_JoinGuildReject(char * Data);
	void NotifyMsg_JoinGuildApprove(char * Data);
	void NotifyMsg_QueryDismissGuildPermission(char * Data);
	void NotifyMsg_QueryJoinGuildPermission(char * Data);
	void NotifyMsg_ItemObtained(char * Data);
	void NotifyMsg_ForceDisconn(char * Data);
	void NotifyMsg_BanGuildMan(char * Data);
	void NotifyMsg_FriendOnGame(char * Data);

	void ResponsePanningHandler(char * Data);
	void _CalcSocketClosed();
	void UpdateScreen_OnSelectServer();
	void StartInputString(int sX, int sY, unsigned char iLen, char * pBuffer, BOOL bIsHide = FALSE);
	void _SetIlusionEffect(int iOwnerH);
	int _iGetFOE(int iStatus);
	void NoticementHandler(char * Data);
	void GetItemName(char * cItemName, DWORD dwAttribute, char *pStr1, char *pStr2, char *pStr3);
	void GetItemName(class CItem * pItem, char * pStr1, char * pStr2, char * pStr3);
	void _InitOnCreateNewCharacter();
	BOOL _bCheckCurrentBuildItemStatus();
	BOOL _bCheckBuildItemStatus();
	BOOL _bDecodeBuildItemContents();
	void GetNpcName(short sType, char * pName);


#ifdef MAKE_ACCOUNT
	int m_iAgreeView;
	void _LoadAgreementTextContents(char cType);
	void UpdateScreen_OnAgreement();
	void UpdateScreen_OnCreateNewAccount();
#endif

	void UpdateFriendsStatus();
	void UseShortCut( int num );
	void UpdateScreen();
	void UpdateScreen_OnMainMenu();
	void UpdateScreen_OnGame();
	void UpdateScreen_OnConnecting();
	void UpdateScreen_OnWaitInitData();
	void MakeSprite( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void MakeLegionSprite( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void MakeTileSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void MakeLegionTileSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void MakeEffectSpr( char* FileName, short sStart, short sCount, bool bAlphaEffect = TRUE);
	void UpdateScreen_OnLoading(bool bActive);
	void UpdateScreen_OnConnectionLost();
	void UpdateScreen_OnLogin();
	void UpdateScreen_OnMsg();
	void UpdateScreen_OnQuit();
	void UpdateScreen_OnQueryForceLogin();
	void UpdateScreen_OnQueryDeleteCharacter();
	void UpdateScreen_OnWaitingResponse();
	void UpdateScreen_OnCreateNewCharacter();
	void UpdateScreen_OnSelectCharacter();
	void UpdateScreen_OnLogResMsg();
	void UpdateScreen_OnSelectCharacter(short sX, short sY, short msX, short msY, BOOL bIgnoreFocus = FALSE);
	void UpdateScreen_OnChangePassword();
	void UpdateScreen_OnLoading_Progress();
	void UpdateScreen_OnVersionNotMatch();
	void NpcTalkHandler(char * Data);
	int  _iGetWeaponSkillType();
	void SetCameraShakingEffect(short sDist, int iMul = 0);
	BOOL bDlgBoxPress_SkillDlg(short msX, short msY);
	BOOL bDlgBoxPress_Inventory(short msX, short msY);
	BOOL bDlgBoxPress_Character(short msX, short msY);
	void ClearSkillUsingStatus();
	BOOL bCheckItemOperationEnabled(char cItemID);
	void _DrawThunderEffect(int sX, int sY, int dX, int dY, int rX, int rY, char cType);
	void DrawLine2(int x0, int y0, int x1, int y1, int iR, int iG, int iB);
	void DrawLine(int x0, int y0, int x1, int y1, int iR, int iG, int iB);
	void SetWhetherStatus(BOOL bStart, char cType);
	void WhetherObjectFrameCounter();
	void DrawWhetherEffects();
	BOOL bCheckLocalChatCommand(char * pMsg);
	char GetOfficialMapName(char * pMapName, char * pName);
	int iGetLevelExp(int iLevel);
	int _iCalcTotalWeight();
	void DrawVersion(BOOL bAuthor = FALSE);
	BOOL _bIsItemOnHand();
	void DynamicObjectHandler(char * Data);
	BOOL _bCheckItemByType(char cType);
	void _DrawBlackRect(int iSize);
	void DrawNpcName(   short sX, short sY, short sOwnerType, int iStatus);
	void DrawObjectName(short sX, short sY, char * pName, int iStatus);
	void PlaySound(char cType, int iNum, int iDist, long lPan = 0);
	void _RemoveChatMsgListByObjectID(int iObjectID);
	void _LoadTextDlgContents(int cType);
	int  _iLoadTextDlgContents2(int iType);
	void DrawChatMsgs(short sX, short sY, short dX, short dY);
	void RequestFullObjectData(WORD wObjectID);
	bool bInitSkillCfgList();
	BOOL bCheckImportantFile();
	void DlbBoxDoubleClick_Inventory(short msX, short msY);
	void DlbBoxDoubleClick_Character(short msX, short msY);
	void DlbBoxDoubleClick_GuideMap(short msX, short msY);
	BOOL _bCheckDlgBoxDoubleClick(short msX, short msY);
	void EraseItem(char cItemID);
	void RetrieveItemHandler(char * Data);
	void CivilRightAdmissionHandler(char * Data);
	void _Draw_CharacterBody(short sX, short sY, short sType);
	void ClearContents_OnSelectCharacter();
	void ClearContents_OnCreateNewAccount();
	void _Draw_UpdateScreen_OnCreateNewAccount();
	BOOL _bDraw_OnCreateNewCharacter(char * pName, short msX, short msY, int iPoint);
	BOOL _bGetIsStringIsNumber(char * pStr);
	BOOL bInitMagicCfgList();
	BOOL __bDecodeContentsAndBuildItemForSaleList(char * pBuffer);
	void _LoadShopMenuContents(char cType);
	void PutChatScrollList(char * pMsg, char cType);
	void RequestTeleportAndWaitData();
	void DrawEffectLights();
	void PointCommandHandler(int indexX, int indexY, char cItemID = -1);
	void DrawEffects();
	void bAddNewEffect(short sType, int sX, int sY, int dX, int dY, char cStartFrame, int iV1 = 1);
	void AddEventList(char * pTxt, char cColor = 0, BOOL bDupAllow = TRUE);
	void ShowEventList(DWORD dwTime);
	void SetItemCount(char * pItemName, DWORD dwCount);
	void _ShiftGuildOperationList();
	void _PutGuildOperationList(char * pName, char cOpMode);
	void DisbandGuildResponseHandler(char * Data);
	void InitPlayerCharacteristics(char * Data);
	void CreateNewGuildResponseHandler(char * Data);
	void _GetHairColorRGB(int iColorType , int * pR, int * pG, int * pB);
	void InitGameSettings();
	void CommonEventHandler(char * Data);
	BOOL _bCheckDraggingItemRelease(short msX, short msY);
	void _SetItemOrder(char cWhere, char cItemID);
	int iGetTopDialogBoxIndex();
	void DisableDialogBox(int iBoxID);
	void EnableDialogBox(int iBoxID, int cType, int sV1, int sV2, char * pString = NULL);
	void InitItemList(char * Data);
	void InitSkillList(char * Data);
	int _iCheckDlgBoxFocus(short msX, short msY, char cButtonSide);
	void GetPlayerTurn();
	BOOL __fastcall DrawObject_OnDead(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnDying(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnMagic(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnAttack(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnAttackMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnStop(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnMove_ForMenu(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnDamageMove(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnRun(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnDamage(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL __fastcall DrawObject_OnGetItem(int indexX, int indexY, int sX, int sY, BOOL bTrans, DWORD dwTime, int msX, int msY);
	BOOL bEffectFrameCounter();
	void ClearGuildNameList();
	void DrawBackground(short sDivX, short sModX, short sDivY, short sModY);
	void DrawChatMsgBox(short sX, short sY, int iChatIndex, BOOL bIsPreDC);
	void ReleaseTimeoverChatMsg();
	void ChatMsgHandler(char * Data);
	void ReleaseUnusedSprites();
	BOOL bReadIp();
	void OnKeyUp(WPARAM wParam);
	void OnSysKeyDown(WPARAM wParam);
	void OnSysKeyUp(WPARAM wParam);
	void ChangeGameMode(char cMode);
	void PutString(int iX, int iY, char * pString, COLORREF color);
	void PutString(int iX, int iY, char * pString, COLORREF color, BOOL bHide, char cBGtype, BOOL bIsPreDC = FALSE);
	void PutString2(int iX, int iY, char * pString, short sR, short sG, short sB);
	void PutAlignedString(int iX1, int iX2, int iY, char * pString, short sR = 0, short sG = 0, short sB = 0);
	void PutString_SprFont(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void PutString_SprFont2(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void PutString_SprFont3(int iX, int iY, char * pStr, short sR, short sG, short sB, BOOL bTrans = FALSE, int iType = 0);
	void PutString_SprNum(int iX, int iY, char * pStr, short sR, short sG, short sB);
	void LogRecvMsgHandler(char * Data);
	void LogResponseHandler(char * Data);
	void OnLogSocketEvent(WPARAM wParam, LPARAM lParam);
	void OnTimer();
	void LogEventHandler(char * Data);
	void _ReadMapData(short sPivotX, short sPivotY, char * Data);
	void MotionEventHandler(char * Data);
	void InitDataResponseHandler(char * Data);
	void InitPlayerResponseHandler(char * Data);
	void ConnectionEstablishHandler(char cWhere);
	void MotionResponseHandler(char * Data);
	void GameRecvMsgHandler(DWORD dwMsgSize, char * Data);
	void DrawObjects(short sPivotX, short sPivotY, short sDivX, short sDivY, short sModX, short sModY, short msX, short msY);
	BOOL bSendCommand(DWORD dwMsgID, WORD wCommand, char cDir, int iV1, int iV2, int iV3, char * pString, int iV4 = NULL); 
	char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, BOOL bMoveCheck = FALSE, BOOL isMIM = FALSE);
	void RestoreSprites();
	void CommandProcessor(short msX, short msY, short indexX, short indexY, char cLB, char cRB, char cMB);
	void OnGameSocketEvent(WPARAM wParam, LPARAM lParam);
	void CalcViewPoint();
	void OnKeyDown(WPARAM wParam);
	void Quit();
	BOOL bInit(HWND hWnd, HINSTANCE hInst, char * pCmdLine);

	void ReserveFightzoneResponseHandler(char * Data);
	int _iGetAttackType();
	BOOL __bDecodeBuildItemContents(char * pBuffer);
	int _iGetBankItemCount();
	int _iGetTotalItemNum();
	LONG GetRegKey(HKEY key, LPCTSTR subkey, LPTSTR retdata);
	void GoHomepage();
	void StartBGM();

	//Snoopy: added function:
	void DebugLog(char * cStr);
	BOOL bReadLoginConfigFile(char * cFn);
	int bHasHeroSet( short Appr3, short Appr4, char OwnerType);
	void ShowHeldenianVictory(short sSide);
	void DrawDialogBox_Resurect(short msX, short msY);
	void DlgBoxClick_Resurect(short msX, short msY);
	void DrawDialogBox_CMDHallMenu(short msX, short msY);
	void DlgBoxClick_CMDHallMenu(short msX, short msY);
	void ResponseHeldenianTeleportList(char *Data);
	void DKGlare(int iWeaponColor, int iWeaponIndex, int *iWeaponGlare);
	void DrawDruncncity();
	void DlgBoxClick_ConfirmExchange(short msX, short msY);
	void Abaddon_corpse(int sX, int sY);
	void DrawAngel(int iSprite, short sX, short sY, char cFrame, DWORD dwTime);

	void LoadMuteList();
	void SaveMuteList();
	
	BOOL _ItemDropHistory(char * ItemName);
	CGame();
	virtual ~CGame();

	struct {
		short sX;
		short sY;
		short sCursorFrame;
		char  cPrevStatus;
		char  cSelectedObjectType;
		short sSelectedObjectID;
		short sPrevX, sPrevY, sDistX, sDistY;
		DWORD dwSelectClickTime;
		short sClickX, sClickY;
	} m_stMCursor;

	struct {
		int   sV1, sV2, sV3, sV4, sV5, sV6, sV7, sV8, sV9, sV10, sV11, sV12, sV13, sV14; 
		DWORD dwV1, dwV2, dwT1;
		BOOL  bFlag;
		short sX, sY;
		short sSizeX, sSizeY;
		short sView;
		char  cStr[32], cStr2[32], cStr3[32], cStr4[32];
		char  cMode;
		BOOL  bIsScrollSelected;
	} m_stDialogBoxInfo[61];	 // Snoopy passé à 61 (origine 41, Alastor 60), j'ai mis +20 car plus pratique.
	char m_cDialogBoxOrder[61];
	int m_bIsDialogEnabled[61];//was BOOL
//Snoopy=>>>>>>>>>>>>>>>>>>>>>
	struct {
		int   sV1, sV2, sV3, sV4, sV5, sV6, sV7, sItemID;
		DWORD dwV1;
		char  cStr1[32], cStr2[32];
	} m_stDialogBoxExchangeInfo[8];
//Snoopy end<<<<<<<<<<<<<<<<<<
	struct {
		int iIndex;
		int iAmount;
	} m_stSellItemList[MAXSELLLIST];

	struct {
		char cName[22];
		char cOpMode;
	} m_stGuildOpList[100];

	struct {
		DWORD dwTime;
		char  cColor;
		char  cTxt[96];
	} m_stEventHistory[6];

	struct {
		DWORD dwTime;
		char  cColor;
		char  cTxt[96];
	} m_stEventHistory2[6];

	struct {
		short sX, sY, sBX;
		char cStep;
	} m_stWhetherObject[MAXWHETHEROBJECTS];

	struct {
		BOOL bIsQuestCompleted;
		short sWho, sQuestType, sContribution, sTargetType, sTargetCount, sX, sY, sRange;
		short sCurrentCount; // by Snoopy
		char cTargetName[22];
	} m_stQuest;

	struct partyMember{
		int hp, mp, Maxhp, Maxmp; 
		BOOL bIsSelected;
		short sX, sY;
		string cName;
		partyMember(char * inName) : cName(inName), sX(0), sY(0) {} 
	}; 

	std::vector<partyMember *> m_stPartyMember;
	typedef std::vector<partyMember *>::iterator partyIterator;

	struct {
		short sX, sY;
		char cType;
		char cSide;
	} m_stCrusadeStructureInfo[MAXCRUSADESTRUCTURES];

	struct {
		DWORD dwRefTime;
		int iGuildRank;
		char cCharName[12];
		char cGuildName[24];
	} m_stGuildName[MAXGUILDNAMES];

	struct {
		int iIndex;
		char mapname[12];
		int iX;
		int iY;
		int iCost;
	} m_stTeleportList[20];

	class YWSound m_DSound;
	class CSoundBuffer *	m_pCSound[MAXSOUNDEFFECTS];
	class CSoundBuffer *	m_pMSound[MAXSOUNDEFFECTS];
	class CSoundBuffer *	m_pESound[MAXSOUNDEFFECTS];
	class CSoundBuffer *    m_pBGM;
	class DXC_ddraw  m_DDraw;
	class DXC_dinput m_DInput;
	class CMisc      m_Misc;
	class CSprite  * m_pSprite[MAXSPRITES];
	class CSprite  * m_pTileSpr[MAXTILES];
	class CSprite  * m_pEffectSpr[MAXEFFECTSPR];
	class CMapData * m_pMapData;
	class XSocket * m_pGSock;
	class XSocket * m_pLSock;
	class CMsg    * m_pChatMsgList[MAXCHATMSGS];
	class CMsg    * m_pChatScrollList[MAXCHATSCROLLMSGS];
	class CMsg    * m_pWhisperMsg[MAXWHISPERMSG];
	class CEffect * m_pEffectList[MAXEFFECTS];
	class CItem   * m_pItemList[MAXITEMS];
	class CItem   * m_pBankList[MAXBANKITEMS];
	class CMagic * m_pMagicCfgList[MAXMAGICTYPE];
	class CSkill * m_pSkillCfgList[MAXSKILLTYPE];
	class CMsg * m_pMsgTextList[TEXTDLGMAXLINES];
	class CMsg * m_pMsgTextList2[TEXTDLGMAXLINES];
	class CMsg * m_pAgreeMsgTextList[TEXTDLGMAXLINES];
	class CBuildItem * m_pBuildItemList[MAXBUILDITEMS];
	class CBuildItem * m_pDispBuildItemList[MAXBUILDITEMS];


	class CItem * m_pItemForSaleList[MAXMENUITEMS];
	class CCharInfo * m_pCharList[4];
	class CItemName * m_pItemNameList[MAXITEMNAMES];
	class CCurse m_curse;

	char * m_pInputBuffer;

	DWORD G_dwGlobalTime;
	DWORD m_dwCommandTime; //v2.15 SpeedHack
	DWORD m_dwConnectMode;
	DWORD m_dwTime;
	DWORD m_dwCurTime;
	DWORD m_dwCheckConnTime, m_dwCheckSprTime, m_dwCheckChatTime;
	DWORD m_dwDialogCloseTime;
	int  m_dwLogOutCountTime;//was DWORD
	DWORD m_dwRestartCountTime;
	DWORD m_dwWOFtime; //v1.4
	DWORD m_dwObserverCamTime;
	DWORD m_dwDamagedTime;
	DWORD m_dwSpecialAbilitySettingTime;
	DWORD m_dwCommanderCommandRequestedTime;
	DWORD m_dwTopMsgTime;
	DWORD m_dwEnvEffectTime;

	//v2.2
	DWORD m_dwMonsterEventTime;
	short m_sMonsterID;
	short m_sEventX, m_sEventY;

	bool m_shieldDisabled;
	bool m_armorDisabled;
	bool m_magicDisabled[MAXMAGICTYPE];

	Side m_side;

	BOOL m_bZoomMap;
	BOOL m_bIsProgramActive;
	int m_bCommandAvailable;//was BOOL
	BOOL m_bSoundFlag;
	BOOL m_bSoundStat, m_bMusicStat; // On/Off
	int m_bIsItemEquipped[MAXITEMS];//was BOOL
	int m_bIsItemDisabled[MAXITEMS];//was BOOL
	int m_bIsGetPointingMode;//was BOOL
	BOOL m_bEnterPressed, m_bEscPressed, m_bCtrlPressed, m_bRunningMode, m_bShiftPressed, m_altPressed;

	BOOL m_bDialogTrans;
	BOOL m_bIsCombatMode;
	BOOL m_bIsSafeAttackMode;
	int m_bSkillUsingStatus;//was BOOL
	int m_bItemUsingStatus;//was BOOL
	BOOL m_bIsWhetherEffect;
	BOOL m_bSuperAttackMode;	//
	BOOL m_bIsObserverMode, m_bIsObserverCommanded;
	int m_bIsPoisoned;//was BOOL
	BOOL m_bIsFirstConn;
	BOOL m_bIsConfusion;
	BOOL m_bIsRedrawPDBGS;
	BOOL m_bDrawFlagDir;
	BOOL m_bIsCrusadeMode;
	BOOL m_bIsAstoriaMode;
	Casualties m_astoriaStats[MAXSIDES];
	DWORD m_relicOwnedTime;
	Side m_relicOwnedSide;
	int m_bIsSpecialAbilityEnabled;//was BOOL
	BOOL m_bInputStatus;
	BOOL m_bToggleScreen;
	BOOL m_bIsSpecial;

	BOOL m_bIsF1HelpWindowEnabled;
	int m_bIsTeleportRequested;//was BOOL
	BOOL m_bIsPrevMoveBlocked;
	BOOL m_bIsHideLocalCursor;

	int m_bForceDisconn;//was BOOL
	BOOL m_bForceAttack;
	BOOL m_bParalyze;

	int m_iFrameCount;
	int m_iFPS;
	DWORD m_dwFPStime;
	BOOL  m_bShowFPS;
	bool  m_showGrid;
	bool  m_showAllDmg;
	bool  m_bigItems;
	bool  m_showTimeStamp;

	int m_iFightzoneNumber;
	int m_iFightzoneNumberTemp;
	int m_iPlayerApprColor; 
	int m_iHP;//was int			// Hit Point
	int m_iMP;//was int			// Mana Point
	int m_iSP;//was int			// Staminar Point
	int m_iAC;						// Armour Class
	int m_iTHAC0;					// To Hit Armour Class 0

	int m_iLevel, m_iExp, m_iContribution;
	int m_stat[6];
	//int m_angelStat[STAT_STR], m_angelStat[STAT_INT], m_angelStat[STAT_DEX], m_angelStat[STAT_MAG];
	int m_angelStat[6];
	char m_createStat[6];
	short m_luStat[6];
	int m_iLU_Point;

	int m_iEnemyKillCount;
	int m_iPKCount;
	int m_iRewardGold;
	int m_iGuildRank, m_iTotalGuildsMan;
	int m_iPointCommandType;
	int m_iTotalChar;
//	int m_iAccountStatus;
	short m_sMagicShortCut;
	int m_iCameraShakingDegree;
	int m_iSuperAttackLeft;
	int m_iAccntYear, m_iAccntMonth, m_iAccntDay;
	int m_iIpYear, m_iIpMonth, m_iIpDay;
	int m_iDownSkillIndex;
	bool IsAccountValid;

	int m_iIlusionOwnerH;
	int m_iApprColor_IE;
	int m_iInputX, m_iInputY;
	int m_iPDBGSdivX, m_iPDBGSdivY;			   // Pre-Draw Background Surface
	short m_sRecentShortCut;
	short m_sShortCut[6]; // Snoopy: 6 shortcuts
	int	m_iSpecialAbilityTimeLeftSec;
	int m_iDrawFlag;
	int m_iSpecialAbilityType;
	int m_iTimeLeftSecAccount, m_iTimeLeftSecIP;
	int m_iCrusadeDuty;
	int m_iLogServerPort;
	int m_iRating; //Rating

	int m_iPrevMoveX, m_iPrevMoveY;
	int m_iBlockYear, m_iBlockMonth, m_iBlockDay;
	unsigned char m_iTopMsgLastSec;
	int m_iConstructionPoint;
	int m_iWarContribution;
	int m_iConstructLocX, m_iConstructLocY;
	int m_iNetLagCount;
	int m_iTeleportLocX, m_iTeleportLocY;
	int m_iTotalPartyMember;
	int m_iPartyStatus;
	int m_iGizonItemUpgradeLeft;
	//int m_iFeedBackCardIndex; // removed by Snoopy

	short m_sItemEquipmentStatus[MAXITEMEQUIPPOS];
	short m_sPlayerX, m_sPlayerY;
	short m_sPlayerObjectID;
	short m_sPlayerType;
	short m_sPlayerAppr1, m_sPlayerAppr2, m_sPlayerAppr3, m_sPlayerAppr4;
	int m_iPlayerStatus;
	short m_sMCX, m_sMCY;
	short m_sCommX, m_sCommY;
	int   m_iCastingMagicType;
	short m_sDamageMove, m_sDamageMoveAmount;
	short m_sAppr1_IE, m_sAppr2_IE, m_sAppr3_IE, m_sAppr4_IE;
	int m_iStatus_IE;
	short m_sViewDstX, m_sViewDstY;
	short m_sViewPointX, m_sViewPointY;
	short m_sVDL_X, m_sVDL_Y;

	WORD m_wCommObjectID;
	WORD m_wEnterGameType;
	WORD m_wR[16], m_wG[16], m_wB[16];
	WORD m_wWR[16], m_wWG[16], m_wWB[16];

	unsigned char m_cInputMaxLen;
	char m_cEdit[4];
	char G_cTxt[128];
	char m_cGameModeCount;
	char m_cBGMmapName[12];
	char m_cItemOrder[MAXITEMS];
	char m_cAmountString[12];
	char m_cLogOutCount;
	char m_cRestartCount;
	char m_cGameMode;
	char m_cWhisperIndex;
	char m_cWhisperName[12];
	char m_cAccountName[12];
	char m_cAccountPassword[12];
	char m_cAccountAge[12];
	char m_cNewPassword[12];
	char m_cNewPassConfirm[12];
	char m_cAccountCountry[18];
	char m_cAccountSSN[32];
	char m_cEmailAddr[52];
	char m_cAccountQuiz[46];// Quiz
	char m_cAccountAnswer[22];
	char m_cPlayerName[12];
	char m_cPlayerDir;
	char m_cMsg[200];
	char m_cLocation[12];
	char m_cCurLocation[12];
	char m_cGuildName[22];
	char m_cMCName[12];
	char m_cMapName[12];
	char m_cMapMessage[32];
	char m_cMapIndex;
	char m_cPlayerTurn;
	char m_cCommand;
	char m_cCurFocus, m_cMaxFocus;
	char m_cEnterCheck, m_cTabCheck, m_cLeftArrowCheck;
	char m_cArrowPressed;
	char m_cLogServerAddr[16];
	char m_cChatMsg[64];
	char m_cBackupChatMsg[64];
	char m_cGender, m_cSkinCol, m_cHairStyle, m_cHairCol, m_cUnderCol;

	char m_cMagicMastery[MAXMAGICTYPE];
	unsigned char m_cSkillMastery[MAXSKILLTYPE]; 
	uint32 m_cash;

	char m_cWorldServerName[32];
	char m_cDetailLevel;
	char m_cMenuDir, m_cMenuDirCnt, m_cMenuFrame;
	char m_cSoundVolume, m_cMusicVolume;
	char m_cWhetherEffectType;
	char m_cWhetherStatus;
	char m_cIlusionOwnerType;
	char m_cName_IE[12];
	char m_sViewDX, m_sViewDY;
	char m_cCommandCount;
	char m_cLoading;
	char m_cDiscount;

	char m_cStatusMapName[12];
	char m_cTopMsg[128];
	char m_cTeleportMapName[12];
	char m_cConstructMapName[12];
	char m_cGameServerName[22]; //  Gateway

	char m_cItemDrop[25][25];

	RECT m_rcPlayerRect, m_rcBodyRect;
	HWND m_hWnd;

	HANDLE m_hPakFile;

	BOOL m_bWhisper;
	BOOL m_bShout;

	BOOL m_bItemDrop;
    int  m_iItemDropCnt;

	// Snoopy: Apocalypse Gate
	char m_cGateMapName[12];
	int  m_iGatePositX, m_iGatePositY;
	int m_iHeldenianAresdenLeftTower;
	int m_iHeldenianElvineLeftTower;
	int m_iHeldenianAresdenFlags;
	int m_iHeldenianElvineFlags;
	int m_iHeldenianAresdenDead;
	int m_iHeldenianElvineDead;
	int m_iHeldenianAresdenKill;
	int m_iHeldenianElvineKill;
	bool m_bIsHeldenianMode;
	bool m_bIsHeldenianMap;

	BOOL m_bIllusionMVT;
	int m_iGameServerMode;
	BOOL m_bIsXmas;
	BOOL m_bUsingSlate;


	//Snoopy: Avatar
	BOOL m_bIsAvatarMode;
	BOOL m_bIsAvatarMessenger;

	//Snoopy: Crafting
	//BOOL _bDecodeCraftItemContents();
	//BOOL __bDecodeCraftItemContents(char *pBuffer);	
	//BOOL _bCheckCraftItemStatus();
	//BOOL _bCheckCurrentCraftItemStatus();

	class CBuildItem * m_pCraftItemList[MAXBUILDITEMS];
	class CBuildItem * m_pDispCraftItemList[MAXBUILDITEMS];
	int   m_iContributionPrice;

	char m_cTakeHeroItemName[100]; 

	int m_levelExpTable[890];

	std::set<string> m_MuteList;

	BOOL m_partyAutoAccept;

	bool m_ekScreenshot;
	DWORD m_ekSSTime;

	bool m_tabbedNotification;
	int m_relicX, m_relicY;

	bool m_manuAutoFill;
};

#endif // !defined(AFX_GAME_H__0089D9E3_74E6_11D2_A8E6_00001C7030A6__INCLUDED_)
