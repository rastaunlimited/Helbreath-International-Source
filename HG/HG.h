// Game.h: interface for the CGame class.
//
//////////////////////////////////////////////////////////////////////

#ifndef AFX_GAME_H__C3D29FC5_755B_11D2_A8E6_00001C7030A6__INCLUDED_
#define AFX_GAME_H__C3D29FC5_755B_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <winbase.h>
#include <process.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <direct.h>
#include <list>

#include "..\shared\common.h"
#include "..\shared\NetMessages.h"
#include "..\shared\items.h"

#include "StrTok.h"
#include "math.h"
#include "net\Xsocket.h"
#include "char\Magic.h"
#include "char\unit.h"
#include "char\Client.h"
#include "char\npc.h"
#include "droplist\dropmanager.h"
#include "map\Map.h"
#include "char\ActionID.h"
#include "net\UserMessages.h"
#include "net\MessageIndex.h"
#include "Misc.h"
#include "net\Msg.h"
#include "char\Skill.h"
#include "map\DynamicObject.h"
#include "char\DelayEvent.h"
#include "char\item\Fish.h"
#include "map\DynamicObject.h"
#include "map\DynamicObjectID.h"
#include "char\item\Potion.h"
#include "char\item\Mineral.h"
#include "char\Quest.h"
#include "char\item\BuildItem.h"
#include "map\TeleportLoc.h"
#include "map\teleport.h"
#include "GlobalDef.h"
#include "englishitem.h"
#include "char\Crafting.h"
#include "astoria.h"
#include "ini.h"

#define SERVERSOCKETBLOCKLIMIT	300

#define MAXCLIENTS			200
#define MAXNPCS				15000
#define MAXMAPS				120
#define MAXBUILDITEMS		300
#define CLIENTTIMEOUT		18 _s
#define AUTOSAVETIME		1 _m
#define HPUPTIME			15 _s
#define MPUPTIME			20 _s
#define SPUPTIME			10 _s

#define HUNGERTIME			10 _m
#define POISONTIME			20 _s
#define SUMMONTIME			5 _m
#define NOTICETIME			80 _s
#define PLANTTIME			5 _m

#define EXPSTOCKTIME		5 _s
#define MSGQUENESIZE		100000
#define AUTOEXPTIME			5 _m

#define TOTALLEVELUPPOINT	3

#define MAXDYNAMICOBJECTS	60000
#define MAXDELAYEVENTS		60000
#define GUILDSTARTRANK		12

#define SSN_LIMIT_MULTIPLY_VALUE	20

#define MAXNOTIFYMSGS		1000
#define NIGHTTIME			40

#define RAGPROTECTIONTIME	7000
#define MAXREWARDGOLD		99999999

#define ATTACKAI_NORMAL				1
#define ATTACKAI_EXCHANGEATTACK		2
#define ATTACKAI_TWOBYONEATTACK		3

#define MAXFISHS					200
#define MAXMINERALS					200
#define MAXENGAGINGFISH				30
#define MAXPOTIONTYPES				500 
#define MAXCRAFTING					120

#define MOBEVENTTIME				300000 // 5Ка 
#define MAXQUESTTYPE				200

#define MAXSUBLOGSOCK				5

#define ITEMLOG_GIVE				1
#define ITEMLOG_DROP				2
#define ITEMLOG_GET					3
#define ITEMLOG_DEPLETE				4
#define ITEMLOG_NEWGENDROP			5
#define ITEMLOG_DUPITEMID			6
#define ITEMLOG_BUY					7        
#define ITEMLOG_SELL				8     
#define ITEMLOG_RETRIEVE			9
#define ITEMLOG_DEPOSIT				10
#define ITEMLOG_EXCHANGE			11
#define ITEMLOG_MAGICLEARN			12
#define ITEMLOG_MAKE				13
#define ITEMLOG_SUMMONMONSTER		14
#define ITEMLOG_POISONED			15
#define ITEMLOG_SKILLLEARN			16
#define ITEMLOG_REPAIR				17
#define ITEMLOG_JOINGUILD           18
#define ITEMLOG_BANGUILD            19
#define ITEMLOG_RESERVEFIGZONE      20	//  "
#define ITEMLOG_APPLY               21	//  "
#define ITEMLOG_SHUTUP              22	//  "
#define ITEMLOG_CLOSECONN			23	//  "
#define ITEMLOG_SPELLFIELD			24	//  "
#define ITEMLOG_CREATEGUILD			25	//  "
#define ITEMLOG_GUILDDISMISS		26	//  "
#define ITEMLOG_SUMMONPLAYER        27	//  "
#define ITEMLOG_CREATE				28	//  "
#define ITEMLOG_UPGRADEFAIL         29
#define ITEMLOG_UPGRADESUCCESS      30


#define ITEMSPREAD_RANDOM			1
#define ITEMSPREAD_FIXED			2
#define MAX_NPCITEMDROP				95


#define CRUSADELOG_ENDCRUSADE       1
#define CRUSADELOG_STARTCRUSADE     2
#define CRUSADELOG_SELECTDUTY       3
#define CRUSADELOG_GETEXP           4
#define CRUSADELOG_APOCALYPSE		5

#define PKLOG_BYPLAYER				1
#define PKLOG_BYPK					2
#define PKLOG_BYENERMY				3
#define PKLOG_BYNPC					4
#define PKLOG_BYOTHER				5
#define PKLOG_REDUCECRIMINAL        6


#define MAXDUPITEMID				100

#define MAXGUILDS					1000
#define MAXONESERVERUSERS			800	 
#define MAXGATESERVERSTOCKMSGSIZE	30000


#define MAXCONSTRUCTNUM			40//raised from 10 to 20 to in corporate 4mana stones

#define MAXSCHEDULE					10



#define MAXFIGHTZONE 10 

//============================
// #define LEVELLIMIT		130
#define LEVELLIMIT		50
//============================

//============================
#define MINIMUMHITRATIO 15
//============================

//============================
#define MAXIMUMHITRATIO	99
//============================

//============================

//============================
#define GMGMANACONSUMEUNIT	35
//============================

#define MAXCONSTRUCTIONPOINT 30000

#define MAXWARCONTRIBUTION	 500000

#define MAXPARTYNUM			200


#define ALLSIDES			100
#define ATTACKER			101
#define DEFENDER			102

//v2.19 2002-11-19 
#define PK					0
#define NONPK				1
#define NEVERNONPK			2  

#define MAX_CRUSADESUMMONMOB	100

#define CRUSADELOG_ENDHELDENIAN		11
#define CRUSADELOG_STARTHELDENIAN	12
#define CRUSADELOG_GETHELDENIANEXP	14
#define CRUSADELOG_HELDENIANVICTORY	15
#define CRUSADELOG_HELDENIANWARNOW	16

#define MAX_HELDENIANTOWER			200
#define MAXHELDENIAN				10
#define MAXHELDENIANSUMMONPOINT		12000	

class CGame  
{
public:
	BOOL bReadSettingsConfigFile(char * cFn);

	int  iGetMapLocationForbiddenSide(char * pMapName);
	void CheckDenialServiceAttack(int iClientH, DWORD dwClientTime, DWORD dwMsgTime, char cKey);
	BOOL bActionOnWrongCRC(int iClientH, int iReason, int iValue = 0);


	void StartHeldenianMode(int iClientH = -1);
	bool bReadHeldenianGUIDFile(char * cFn);
	void _CreateHeldenianGUID(DWORD m_dwHeldenianGUID, int m_iHeldenianType1Winner, int m_iHeldenianType2Winner, int m_iHeldenianType) const;
	bool SetHeldenianFlag(char cMapIndex, int dX, int dY, int iSide, int iEKNum, int iClientH, int code);
	void UpdateHeldenianStatus() const;	
	void HeldenianEndWarNow(int m_iHeldenianType, Side side);
	void CheckHeldenianResultCalculation(int iClientH) const;
	void RequestHeldenianScroll(int iClientH, char * pData, DWORD dwMsgSize);
	void HeldenianPlayerKill(CClient * killer, CClient * victim);

	void Apocalypse_MonsterCount(int iClientH);
	void DoAbaddonThunderDamageHandler(char cMapIndex);
	void SendThunder(int iClient, short sX, short sY, short sV3, short sV4);
	void LocalEndApocalypse();
	void LocalStartApocalypse();
	void GlobalEndApocalypseMode(int iClientH);
	void GlobalStartApocalypseMode(int iClientH);
	void GenerateApocalypseBoss(int MapIndex);
	void Notify_ApocalypseGateState(int iClientH);
	void Use_ApocalypseGate(int iClientH);
	void Open_EmptyMap_Gate(int MapIndex);
	void GenerateSlime(int MapIndex);

	int  iSetSide(int iClientH); 
	bool _bCrusadeLog(int iAction,int iClientH,int iData, char * cName);
	void SetForceRecallTime(int iClientH) ; 
	bool bCheckClientMoveFrequency(int iClientH, DWORD dwClientTime); 
	bool bCheckClientMagicFrequency(int iClientH, DWORD dwClientTime); 
	bool bCheckClientAttackFrequency(int iClientH, DWORD dwClientTime); 
	void RequestGuildNameHandler(int iClientH, int iObjectID, int iIndex); 
	void ArmorLifeDecrement(int iClientH, int sTargetH, char cOwnerType, int iValue);
	bool bCheckIsItemUpgradeSuccess(int iClientH, int iItemIndex, int iSomH,bool bBonus = FALSE) ;
	void RequestItemUpgradeHandler(int iClientH, int iItemIndex);
	void GetExp(int iClientH, int iExp, bool bIsAttackerOwn = FALSE);
	void PartyOperationResult_Dismiss(int iClientH, char *pName, int iResult, int iPartyID);
	void RequestAcceptJoinPartyHandler(int iClientH, int iResult);
	void RequestDeletePartyHandler(int iClientH);
	void PartyOperationResult_Info(int iClientH, char * pName, int iTotal, char * pNameList);
	void GetPartyInfoHandler(int iClientH);
	void RequestDismissPartyHandler(int iClientH);
	void PartyOperationResult_Join(int iClientH, char *pName, int iResult, int iPartyID);
	void RequestJoinPartyHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void PartyOperationResult_Delete(int iPartyID);
	void PartyOperationResult_Create(int iClientH, char * pName, int iResult, int iPartyID);
	void PartyOperationResultHandler(char * pData);
	void RequestCreatePartyHandler(int iClientH);
	void ResurrectPlayer(int iClientH);
	void AdminOrder_GetFightzoneTicket(int iClientH);
	void KillCrusadeObjects();
	void AdminOrder_CheckRep(int iClientH, char * pData,DWORD dwMsgSize);
	void AdminOrder_CleanMap(int iClientH, char * pData, DWORD dwMsgSize);

	void RequestUpdateFriendsHandler(int iClientH, char *pData, DWORD dwMsgSize);
	void GSM_RequestFindFriend(WORD reqServerID, WORD reqClientH, char * requesterName, char * names, WORD nameSize);

	bool bReadSchedulerConfigFile(char * pFn);
	void Scheduler();
	bool bCopyItemContents(CItem * pOriginal, CItem * pCopy);

	int  iGetMapLocationSide(char * pMapName);
	int WriteItemData(char * buffer, CItem * pItem);
	bool WriteTileData(char * buffer, int & sizeWritten, int iClientH, CTile * srcTile, int ix, int iy);

	void ManualEndCrusadeMode(int m_iCrusadeWinnerSide);
	void ChatMsgHandlerGSM(int iMsgType, int iV1, char * pName, char * pData, DWORD dwMsgSize);
	bool bReadCrusadeGUIDFile(char * cFn);
	void _CreateCrusadeGUID(DWORD dwCrusadeGUID, int m_iCrusadeWinnerSide);
	void RemoveClientShortCut(int iClientH);
	bool bAddClientShortCut(int iClientH);
	void RequestSetGuildConstructLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char * pMapName);
	void GSM_SetGuildConstructLoc(int iGuildGUID, int dX, int dY, char * pMapName);
	void GSM_ConstructionPoint(int iGuildGUID, int iPoint);
	void CheckCommanderConstructionPoint(int iClientH);
	void GlobalStartCrusadeMode();
	void GSM_SetGuildTeleportLoc(int iGuildGUID, int dX, int dY, char * pMapName);
	void SyncMiddlelandMapInfo();
	void _GrandMagicLaunchMsgSend(int iType, char cAttackerSide);

	void GrandMagicResultHandler(char * cMapName, int iCrashedStructureNum, int iStructureDamageAmount, int iCasualities, int iActiveStructure, int iSTCount,char * pData);
	void CalcMeteorStrikeEffectHandler(int iMapIndex);
	void DoMeteorStrikeDamageHandler(int iMapIndex);
	void GSM_RequestFindCharacter(WORD wReqServerID, WORD wReqClientH, char * pName,char * cCharName);

	void GSM_RequestShutupPlayer(char * cName,WORD wReqServerID, WORD wReqClientH, WORD wV1,char * cTemp); 
	void ServerStockMsgHandler(char * pData);
	void SendStockMsgToGateServer();
	bool bStockMsgToGateServer(char * pData, DWORD dwSize);
	void RequestHelpHandler(int iClientH);
	
	void ReqCreateCraftingHandler(int iClientH, char *pData);
	BOOL _bDecodeCraftingConfigFileContents(char * pData, DWORD dwMsgSize);

	void _SendMapStatus(int iClientH);
	void MapStatusHandler(int iClientH, int iMode, char * pMapName);
	void SelectCrusadeDutyHandler(int iClientH, int iDuty);

	void CheckConnectionHandler(int iClientH, char *pData);
	void RequestSummonWarUnitHandler(int iClientH, int dX, int dY, char cType, char cNum, char cMode);
	void RequestGuildTeleportHandler(int iClientH);
	void RequestSetGuildTeleportLocHandler(int iClientH, int dX, int dY, int iGuildGUID, char * pMapName);
	void MeteorStrikeHandler(int iMapIndex);
	void _LinkStrikePointMapIndex();
	void MeteorStrikeMsgHandler(char cAttackerSide);
	void SendCollectedMana();
	void CreateCrusadeStructures();

	bool bReadCrusadeStructureConfigFile(char * cFn);
	void SaveOccupyFlagData();
	void LocalEndCrusadeMode(int crusadeWinnerSide);
	void LocalStartCrusadeMode(DWORD dwGuildGUID);
	void CheckCrusadeResultCalculation(int iClientH);

	bool __bSetConstructionKit(int iMapIndex, int dX, int dY, int iType, int iTimeCost, int iClientH);
	bool __bSetAgricultureItem(int iMapIndex, int dX, int dY, int iType, int iSsn,int iClientH);   
	bool bCropsItemDrop(int iClientH, short iTargetH,bool bMobDropPos = FALSE);
	void AgingMapSectorInfo();
	void UpdateMapSectorInfo();

	bool bGetItemNameWhenDeleteNpc(int & iItemID, short sNpcType, int iItemprobability);

	int iGetItemWeight(CItem * pItem, int iCount = 1);
	void CancelQuestHandler(int iClientH);
	void ActivateSpecialAbilityHandler(int iClientH);
	void EnergySphereProcessor(bool bIsAdminCreate = FALSE, int iClientH = NULL);
	bool bCheckEnergySphereDestination(int iNpcH, short sAttackerH, char cAttackerType);
	void JoinPartyHandler(int iClientH, int iV1, char * pMemberName);
	void CreateNewPartyHandler(int iClientH);
	void DeleteOccupyFlags(int iMapIndex);
	void RequestSellItemListHandler(int iClientH, char * pData);
	void AdminOrder_CreateItem(int iClientH, char * pData, DWORD dwMsgSize);
	void RequestRestartHandler(int iClientH);
	void AdminOrder_SetObserverMode(int iClientH);
	int iRequestPanningMapDataRequest(int iClientH, char * pData);
	void GetMagicAbilityHandler(int iClientH);
	void Effect_Damage_Spot_DamageMove(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sAtkX, short sAtkY, short sV1, short sV2, short sV3, bool bExp, int iAttr);
	void _TamingHandler(int iClientH, int iSkillNum, char cMapIndex, int dX, int dY);
	void RequestCheckAccountPasswordHandler(char * pData, DWORD dwMsgSize);
	int _iTalkToNpcResult_Guard(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	void _bDecodeNoticementFileContents(char * pData, DWORD dwMsgSize);
	void RequestNoticementHandler(int iClientH, char * pData);
	bool _bCheckDupItemID(CItem * pItem);
	bool _bDecodeDupItemIDFileContents(char * pData, DWORD dwMsgSize);
	void NpcDeadItemGenerator(int iNpcH, short sAttackerH, char cAttackerType);
	uint32 RollMultiple(CNpc * npc, int iItemSpreadType, int iSpreadRange, int *iItemIDs, Point *BasePos);
	void AdminOrder_DisconnectAll(int iClientH);
	void AdminOrder_Summon(int iClientH, char * pData, DWORD dwMsgSize);

	void AdminOrder_SummonPlayer(int iClientH, char * pData, DWORD dwMsgSize);


	char _cGetSpecialAbility(int iKindSA);
	void AdminOrder_UnsummonBoss(int iClientH);
	void AdminOrder_UnsummonAll(int iClientH);
	void AdminOrder_SetAttackMode(int iClientH, char * pData, DWORD dwMsgSize);

	void AdminOrder_ToggleInvincible(int iClientH);
	void AdminOrder_ToggleNoAggro(int iClientH);

	void AdminOrder_SetForceRecallTime(int iClientH, char * pData, DWORD dwMsgSize);

	void AdminOrder_EventSpell(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_EventArmor(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_EventSheild(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_EventChat(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_EventParty(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_EventReset(int iClientH);
	void AdminOrder_EventTP(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_EventIllusion(int iClientH, char * pData, DWORD dwMsgSize);

	void BuildItemHandler(int iClientH, char * pData);
	bool _bDecodeBuildItemConfigFileContents(char * pData, DWORD dwMsgSize);
	bool _bCheckSubLogSocketIndex();

	bool _bItemLog(int iAction, int iGiveH, int iRecvH, CItem * pItem, bool bForceItemLog = FALSE) ;
	bool _bItemLog(int iAction, int iClientH, char * cName, CItem * pItem);

	bool _bPKLog(int iAction, int iAttackerH, int iVictumH, char * cNPC) ;

	void OnSubLogRead(int iIndex);
	void OnSubLogSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	void _CheckStrategicPointOccupyStatus(char cMapIndex);
	void GetMapInitialPoint(int iMapIndex, short * pX, short * pY, char * pPlayerLocation = NULL);
	void _ClearQuestStatus(int iClientH);
	bool _bCheckItemReceiveCondition(int iClientH, CItem * pItem);
	void SendItemNotifyMsg(int iClientH, WORD wMsgType, CItem * pItem, int iV1, bool deleteOnError);

	int _iTalkToNpcResult_WTower(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_WHouse(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_BSmith(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_GShop(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_GuildHall(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	bool _bCheckIsQuestCompleted(int iClientH);
	void _CheckQuestEnvironment(int iClientH);
	void _SendQuestContents(int iClientH);
	void QuestAcceptedHandler(int iClientH);
	bool _bDecodeQuestConfigFileContents(char * pData, DWORD dwMsgSize);
	void CancelExchangeItem(int iClientH);
	bool bAddItem(int iClientH, CItem * pItem);
	void ConfirmExchangeItem(int iClientH);
	void SetExchangeItem(int iClientH, int iItemIndex, int iAmount);
	void ExchangeItemHandler(int iClientH, short sItemIndex, int iAmount, short dX, short dY, WORD wObjectID, char * pItemName);


	void _Manager_Init(int iClientH, char * pData);
	void _Manager_Shutdown(int iClientH, char * pData);


	void CheckUniqueItemEquipment(int iClientH);
	void _SetItemPos(int iClientH, char * pData);
	void GetHeroMantleHandler(int iClientH,int iItemID,char * pString);

	bool _bDecodeOccupyFlagSaveFileContents(char * pData, DWORD dwMsgSize);
	void GetOccupyFlagHandler(int iClientH);
	int  _iComposeFlagStatusContents(char * pData);
	void SetSummonMobAction(int iClientH, int iMode, DWORD dwMsgSize, char * pData = NULL);
	bool __bSetOccupyFlag(char cMapIndex, int dX, int dY, int iSide, int iEKNum, int iClientH, bool bAdminFlag);
	bool _bDepleteDestTypeItemUseEffect(int iClientH, int dX, int dY, short sItemIndex, short sDestItemID);
	void SetDownSkillIndexHandler(int iClientH, int iSkillIndex);
	int iGetComboAttackBonus(int iSkill, int iComboCount);
	int  _iGetWeaponSkillType(int iClientH);
	void AdminOrder_GetNpcStatus(int iClientH, char * pData, DWORD dwMsgSize);
	void CheckFireBluring(char cMapIndex, int sX, int sY);
	void NpcTalkHandler(int iClientH, int iWho);
	bool bDeleteMineral(int iIndex);
	void DeleteFlags();
	void _CheckMiningAction(int iClientH, int dX, int dY);
	int iCreateMineral(char cMapIndex, int tX, int tY, char cLevel);
	void MineralGenerator();
	void LocalSavePlayerData(int iClientH);
	bool _bDecodePotionConfigFileContents(char * pData, DWORD dwMsgSize);
	void ReqCreatePotionHandler(int iClientH, char * pData);
	void _CheckAttackType(int iClientH, short * spType);
	bool bOnClose();
	void AdminOrder_SetInvi(int iClientH);
	void AdminOrder_SetHP(int iClientH, uint32 val);
	void AdminOrder_SetMP(int iClientH, uint32 val);
	void AdminOrder_SetMag(int iClientH, uint32 val);
	void AdminOrder_Polymorph(int iClientH, char * pData, DWORD dwMsgSize);
	void ForceDisconnectAccount(char * pAccountName, WORD wCount);
	void NpcRequestAssistance(int iNpcH);
	void ToggleSafeAttackModeHandler(int iClientH);
	void AdminOrder_CheckIP(int iClientH, char * pData, DWORD dwMsgSize);
	void SpecialEventHandler();
	int _iForcePlayerDisconect(int iNum);
	void AdminOrder_Teleport(int iClientH, char * pData, DWORD dwMsgSize);
	int iGetMapIndex(char * pMapName);
	int iGetWhetherMagicBonusEffect(short sType, char cWheatherStatus);
	void WhetherProcessor();
	int getPlayerNum(char cMapIndex, short dX, short dY, char cRadius);
	void FishGenerator();
	void ReqGetFishThisTimeHandler(int iClientH);
	void AdminOrder_CreateFish(int iClientH, char * pData, DWORD dwMsgSize);
	void FishProcessor();
	int iCheckFish(int iClientH, char cMapIndex, short dX, short dY);
	bool bDeleteFish(int iHandle, int iDelMode);
	int  iCreateFish(char cMapIndex, short sX, short sY, short sDifficulty, CItem * pItem, int iDifficulty, DWORD dwLastTime);
	void UserCommand_DissmissGuild(int iClientH, char * pData, DWORD dwMsgSize);

	void UserCommand_BanGuildsman(int iClientH, char * pData, DWORD dwMsgSize);

	void AdminOrder_ReserveFightzone(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_CloseConn(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_CallGuard(int iClientH, char * pData, DWORD dwMsgSize);
	int iGetExpLevel(int iExp);
	void CalcExpStock(int iClientH);
	void ResponseSavePlayerDataReplyHandler(char * pData, DWORD dwMsgSize);
	void NoticeHandler();
	bool bReadNotifyMsgListFile(char * cFn);
	void SetPlayerReputation(int iClientH, char * pMsg, char cValue, DWORD dwMsgSize);
	void ShutUpPlayer(int iClientH, char * pMsg, DWORD dwMsgSize);
	void CheckDayOrNightMode();
	bool bCheckBadWord(char * pString);
	void PoisonEffect(int iClientH, int iV1);
	void bSetNpcAttackMode(char * cName, int iTargetH, char cTargetType, bool bIsPermAttack);
	bool _bGetIsPlayerHostile(int iClientH, int sOwnerH);
	bool bAnalyzeCriminalAction(int iClientH, short dX, short dY, bool bIsCheck = FALSE);
	void CalcTotalItemEffect(int iClientH, int iEquipItemID, bool bNotify = TRUE);
	void GetPlayerProfile(int iClientH, char * pMsg, DWORD dwMsgSize);
	void SetPlayerProfile(int iClientH, char * pMsg, DWORD dwMsgSize);
	void ToggleWhisperPlayer(int iClientH, char * pMsg, DWORD dwMsgSize);
	void CheckAndNotifyPlayerConnection(int iClientH, char * pMsg, DWORD dwSize);
	int iCalcTotalWeight(int iClientH);
	void ReqRepairItemCofirmHandler(int iClientH, char cItemID, char * pString);
	void ReqRepairItemHandler(int iClientH, char cItemID, char cRepairWhom, char * pString);
	void ReqSellItemConfirmHandler(int iClientH, char cItemID, int iNum, char * pString);
	void ReqSellItemHandler(int iClientH, char cItemID, char cSellToWhom, int iNum, char * pItemName);
	void UseSkillHandler(int iClientH, int iV1, int iV2, int iV3);
	int  iCalculateUseSkillItemEffect(int iOwnerH, char cOwnerType, char cOwnerSkill, int iSkillNum, char cMapIndex, int dX, int dY);
	void ClearSkillUsingStatus(int iClientH);
	void DynamicObjectEffectProcessor();
	int _iGetTotalClients();
	void SendObjectMotionRejectMsg(int iClientH);
	bool RemoveFromDelayEventList(int iH, char cType, int iEffectType);
	bool RemoveFromDelayEventList(Unit * unit, int iEffectType);
	void DelayEventProcessor();
	bool RegisterDelayEvent(int iDelayType, int iEffectType, DWORD dwLastTime, int iTargetH, char cTargetType, char cMapIndex, int dX, int dY, int iV1, int iV2, int iV3);
	bool RegisterDelayEvent(int iDelayType, int iEffectType, DWORD dwLastTime, Unit * unit, char cMapIndex, int dX, int dY, int iV1, int iV2, int iV3);
	int iGetFollowerNumber(short sOwnerH, char cOwnerType);
	int  _iCalcSkillSSNpoint(int iLevel);
	void OnKeyUp(WPARAM wParam, LPARAM lParam);
	void OnKeyDown(WPARAM wParam, LPARAM lParam);
	bool bSetItemToBankItem(int iClientH, CItem * pItem);
	void Effect_SpDown_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3);
	void Effect_HpUp_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3);
	void Effect_Damage_Spot(short sAttackerH, char cAttackerType, short sTargetH, char cTargetType, short sV1, short sV2, short sV3, bool bExp, int iAttr = NULL);
	void UseItemHandler(int iClientH, short sItemIndex, short dX, short dY, short sDestItemID);

	void ItemDepleteHandler(int iClientH, short sItemIndex, bool bIsUseItemResult, bool bIsLog = TRUE);
	int _iGetArrowItemIndex(int iClientH);
	void RequestFullObjectData(int iClientH, char * pData, int objectID = -1);
	void DeleteNpc(int iNpcH);
	void nextWaypointDest(int iNpcH);
	void MobGenerator();
	void CheckDynamicObjectList();
	int  iAddDynamicObjectList(short sOwner, char cOwnerType, short sType, char cMapIndex, short sX, short sY, DWORD dwLastTime, int iV1 = NULL);
	int _iCalcMaxLoad(int iClientH);
	void GetRewardMoneyHandler(int iClientH);
	void EnemyKillRewardHandler(int iAttackerH, int iClientH);
	void PK_KillRewardHandler(short sAttackerH, short sVictimH);
	bool bSetItemToBankItem(int iClientH, short sItemIndex);
	void RequestRetrieveItemHandler(int iClientH, char * pData);
	void RequestCivilRightHandler(int iClientH, char * pData);
	bool bCheckLimitedUser(int iClientH);
	void LevelUpSettingsHandler(int iClientH, char * pData, DWORD dwMsgSize);

	void FightzoneReserveHandler(int iClientH, char * pData, DWORD dwMsgSize);
	bool bCheckLevelUp(int iClientH);
	int iGetLevelExp(int iLevel);
	void TimeManaPointsUp(int iClientH);
	void TimeStaminarPointsUp(int iClientH);
	void Quit();

	int  _iGetSkillNumber(char * pSkillName);
	void TrainSkillResponse(bool bSuccess, int iClientH, int iSkillNum, int iSkillLevel);
	int _iGetMagicNumber(char * pMagicName, int * pReqInt, int * pCost);
	void RequestStudyMagicHandler(int iClientH, char * pName, bool bIsPurchase = TRUE);
	bool _bDecodeSkillConfigFileContents(char * pData, DWORD dwMsgSize);
	bool _bDecodeMagicConfigFileContents(char * pData, DWORD dwMsgSize);
	void ReleaseFollowMode(short sOwnerH, char cOwnerType);
	bool bSetNpcFollowMode(char * pName, char * pFollowName, char cFollowOwnerType);
	void RequestTeleportHandler(int iClientH, char recallType, char * cMapName = NULL, int dX = -1, int dY = -1);
	void PlayerMagicHandler(int iClientH, int dX, int dY, short sType, bool bItemEffect = FALSE, int iV1 = NULL);
	int  iClientMotion_Magic_Handler(int iClientH, short sX, short sY, char cDir);
	void ToggleCombatModeHandler(int iClientH); 
	void GuildNotifyHandler(char * pData, DWORD dwMsgSize);
	void SendGuildMsg(int iClientH, WORD wNotifyMsgType, short sV1, short sV2, char * pString);
	void TimeHitPointsUp(int iClientH);
	void CalculateGuildEffect(int iVictimH, char cVictimType, short sAttackerH);
	void OnStartGameSignal();
	bool _binitNpcAttr(CNpc * pNpc, char * pNpcName, short sClass, char cSA);
	bool _bDecodeNpcConfigFileContents(char * pData, DWORD dwMsgSize);
	void ReleaseItemHandler(int iClientH, short sItemIndex, bool bNotice);
	int  SetItemCount(int iClientH, char * pItemName, DWORD dwCount);
	int  SetItemCount(int iClientH, int iItemIndex, DWORD dwCount);
	DWORD dwGetItemCount(int iClientH, char * pName);
	void DismissGuildRejectHandler(int iClientH, char * pName);
	void DismissGuildApproveHandler(int iClientH, char * pName);
	void JoinGuildRejectHandler(int iClientH, char * pName);			    
	void JoinGuildApproveHandler(int iClientH, char * pName);
	void SendNotifyMsg(int iFromH, int iToH, WORD wMsgType, DWORD sV1, DWORD sV2, DWORD sV3, const char * pString, 
		DWORD sV4 = NULL, DWORD sV5 = NULL, DWORD sV6 = NULL, DWORD sV7 = NULL, DWORD sV8 = NULL, 
		DWORD sV9 = NULL, char * pString2 = NULL) const;
	void GiveItemHandler(int iClientH, short sItemIndex, int iAmount, short dX, short dY, WORD wObjectID, char * pItemName);
	void RequestPurchaseItemHandler(int iClientH, char * pItemName, int iNum);
	void ResponseDisbandGuildHandler(char * pData, DWORD dwMsgSize);
	void RequestDisbandGuildHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void RequestCreateNewGuildHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void ResponseCreateNewGuildHandler(char * pData, DWORD dwMsgSize);
	int  iClientMotion_Stop_Handler(int iClientH, short sX, short sY, char cDir);

	bool bEquipItemHandler(int iClientH, short sItemIndex, bool bNotify = TRUE);
	bool _bAddClientItemList(int iClientH, CItem * pItem, int * pDelReq);
	int  iClientMotion_GetItem_Handler(int iClientH, short sX, short sY, char cDir);
	void DropItemHandler(int iClientH, short sItemIndex, int iAmount, char * pItemName, bool bByPlayer = FALSE);
	void ClientCommonHandler(int iClientH, char * pData);
	bool __fastcall bGetMsgQuene(char * pFrom, char * pData, DWORD * pMsgSize, int * pIndex, char * pKey);
	void MsgProcess();
	bool __fastcall bPutMsgQuene(char cFrom, char * pData, DWORD dwMsgSize, int iIndex, char cKey);
	void NpcBehavior_Flee(int iNpcH);
	void NpcBehavior_Dead(int iNpcH);
	void NpcKilledHandler(short sAttackerH, char cAttackerType, int iNpcH, short sDamage);
	void RemoveFromTarget(short sTargetH, char cTargetType, int iCode = NULL);
	void RemoveFromTarget(Unit * target, int iCode = NULL);
	bool bGetEmptyPosition(short * pX, short * pY, char cMapIndex);
	char cGetNextMoveDir(short sX, short sY, short dstX, short dstY, char cMapIndex, char cTurn, int * pError);
	int  iClientMotion_Attack_Handler(int iClientH, short sX, short sY, short dX, short dY, short wType, char cDir, WORD wTargetObjectID, bool bRespose = TRUE, bool bIsDash = FALSE);
	void ChatMsgHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void NpcProcess();
	bool bCreateNewNpc(char * pNpcName, char * pName, char * pMapName, char cSA, char cMoveType, int * poX, int * poY, char * pWaypointList, RECT * pArea, int iSpotMobIndex, char cChangeSide, bool bHideGenMode, bool bIsSummoned = FALSE, bool bFirmBerserk = FALSE, bool bIsMaster = FALSE, int iGuildGUID = NULL);
	//bool bCreateNewNpc(char * pNpcName, char * pName, char * pMapName, short sX, short sY);
	bool _bReadMapInfoFiles(int iMapIndex);

	bool _bGetIsStringIsNumber(char * pStr);
	bool _bInitItemAttr(CItem * pItem, char * pItemName);

	bool _bInitItemAttr(CItem * pItem, int iItemID);
	bool bReadProgramConfigFile(char * cFn);
	void InitPlayerData(int iClientH, char * pData, DWORD dwSize);
	void ResponsePlayerDataHandler(char * pData, DWORD dwSize);
	void RequestInitDataHandler(int iClientH);
	void RequestInitPlayerHandler(int iClientH, char * pData, char cKey);
	void PlayerMapEntry(int iClientH, bool setRecallTime = true);


	bool bSendMsgToLS(DWORD dwMsg, int iClientH, bool bFlag = TRUE,char * pData = NULL );
	void CheckClientResponseTime();
	void OnTimer(char cType);
	int iComposeMoveMapData(short sX, short sY, int iClientH, char cDir, char * pData);
	void SendEventToNearClient_TypeB(DWORD dwMsgID, WORD wMsgType, char cMapIndex, short sX, short sY, short sV1 = 0, short sV2 = 0, short sV3 = 0, short sV4 = 0);
	void SendEventToNearClient_TypeA(short sOwnerH, char cOwnerType, DWORD dwMsgID, WORD wMsgType, short sV1, short sV2, short sV3);
	void DeleteClient(int iClientH, bool bSave, bool bNotify, bool bCountLogout = TRUE, bool bForceCloseConn = FALSE);
	int  iComposeInitMapData(short sX, short sY, int iClientH, char * pData);
	int  iClientMotion_Move_Handler(int iClientH, short sX, short sY, char cDir, bool bIsRun);
	void ClientMotionHandler(int iClientH, char * pData);
	void DisplayInfo(HDC hdc);
	void OnClientRead(int iClientH);
	bool bInit();
	void OnClientSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	bool bAccept(XSocket * pXSock);
	void PlayerOrder_SetAFK(int iClientH);


	void GetFightzoneTicketHandler(int iClientH);

	void FightzoneReserveProcessor() ;

	// 2002-10-23 Item Event
	bool NpcDeadItemGeneratorWithItemEvent(int iNpcH, short sAttackerH, char cAttackerType);

	bool bCheckInItemEventList(int iItemID, int iNpcH);


	bool _bDecodeTeleportListConfigFileContents(char * pData, DWORD dwMsgSize);

	void RequestTeleportListHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void RequestChargedTeleportHandler(int iClientH, char *pData, DWORD dwMsgSize);
	void RequestResurrectPlayer(int iClientH, bool bResurrect);
	void StateChangeHandler(int iClientH, char * pData, DWORD dwMsgSize);
	BOOL CheckMagicInt(int iClientH);
	BOOL ChangeState(char cStateChange, char* cStr, char *cVit,char *cDex,char *cInt,char *cMag,char *cChar);

	void RequestSetRecallPoint(int iClientH, char * pData, DWORD dwMsgSize);

	struct 
	{
		CItem * item;
		DWORD dropTime;
		short sx, sy;
		char cMapIndex;
		BOOL bEmpty;
	} m_stGroundNpcItem[MAXGROUNDITEMS];
	void TileCleaner();
	void AddGroundItem(CItem * pItem, short x, short y, char mapIndex, DWORD dwTime);

	// Legion point functions
	void HandleLegionService(char * data);
	bool ChangeNation(int clientH, Side side);
	void SubstractCash(char * account, WORD cmd);
	bool GetLegionGold(int clientH, long count);
	bool GetLegionItem(int clientH, WORD cmd);

	uint32 FindNPC(const string npcName);
	uint32 FindItem(const string itemName);

	void EventStart(EventType eType);
	void EventEnd();
	void NotifyEventStats(const Casualties * stats) const;
	void NotifyRelicInAltar(const Side altarSide) const;
	void NotifyRelicGrabbed(const CClient * picker) const;
	void ShuffleAstoriaBasePos();
	void CreateAstoriaFlags();
	void UpdateRelicPos(int iClientH = NULL);

	void UpdateWebsiteStats();
	void OnWebSocketEvent(UINT message, WPARAM wParam, LPARAM lParam);
	//=======================================================================================
	bool IsDatePast(char *Date);
	//=======================================================================================

	CGame(HWND hWnd);
	~CGame();

	char m_cServerName[12];
	char WorldName[12];
	char m_cGameServerAddr[16];
	char m_cGameServerAddrExternal[16];
	char m_cLogServerAddr[16];
	int  m_iGameServerPort;
	int  m_iLogServerPort;
	int  m_iGateServerPort;
	int  m_iWorldLogServerPort;
	char m_cLogServerAddrExternal[16];
	int  m_iGameServerMode;
	int  m_iLimitedUserExp, m_iLevelExp51;

//private:
	bool _bDecodeItemConfigFileContents(char * pData, DWORD dwMsgSize);
	int _iComposePlayerDataFileContents(int iClientH, char * pData);
	bool _bDecodePlayerDatafileContents(int iClientH, char * pData, DWORD dwSize);
	bool _bRegisterMap(char * pName);

	CClient * m_pClientList[MAXCLIENTS];
	CNpc    * m_pNpcList[MAXNPCS];
	DropManager	m_drops;
	class CMap    * m_pMapList[MAXMAPS];
	CDynamicObject * m_pDynamicObjectList[MAXDYNAMICOBJECTS];
	CDelayEvent    * m_pDelayEventList[MAXDELAYEVENTS];

	CMsg    * m_pMsgQuene[MSGQUENESIZE];
	int             m_iQueneHead, m_iQueneTail;
	int             m_iTotalMaps;
	CMisc     m_Misc;
	bool			m_bIsGameStarted;
	bool			ReceivedAllConfig;
	bool			m_bIsGameServerRegistered;
	bool			m_bIsSocketConnected[MAXSUBLOGSOCK];
	bool			m_bIsItemAvailable, m_bIsBuildItemAvailable, m_bIsNpcAvailable, m_bIsMagicAvailable;
	bool			m_bIsSkillAvailable, m_bIsPotionAvailable, m_bIsQuestAvailable;
	CItem   * m_pItemConfigList[MAXITEMTYPES];
	CNpc    * m_npcConfigList[MAXNPCTYPES];
	CMagic  * m_pMagicConfigList[MAXMAGICTYPE];
	CSkill  * m_pSkillConfigList[MAXSKILLTYPE];
	CQuest  * m_pQuestConfigList[MAXQUESTTYPE];
	char            m_pMsgBuffer[MSGBUFFERSIZE+1];
	CCrafting * m_pCraftingConfigList[MAXCRAFTING];

	CTeleport * m_pTeleportConfigList[MAXTELEPORTLIST];

	HWND  m_hWnd;
	int   m_iTotalClients, m_iMaxClients, m_iTotalGameServerClients, m_iTotalGameServerMaxClients;

	bool  m_bF1pressed, m_bF4pressed, m_bF12pressed;
	bool  m_bOnExitProcess;
	DWORD m_dwExitProcessTime;

	DWORD m_dwWhetherTime, m_dwGameTime1, m_dwGameTime2, m_dwGameTime3, m_dwGameTime4, m_dwGameTime5, m_dwGameTime6, m_dwFishTime;

	char  m_cDayOrNight;
 	int   m_iSkillSSNpoint[102];

	CMsg * m_pNoticeMsgList[MAXNOTIFYMSGS];
	int   m_iTotalNoticeMsg, m_iPrevSendNoticeMsg;
	DWORD m_dwNoticeTime, m_dwSpecialEventTime, m_startTime;
	bool  m_bIsSpecialEventTime;
	char  m_cSpecialEventType;
	uint32 m_onlineCntAdd;

	int  m_iClientConnectionCheckTime;
	int  m_iClientConnectionCheckMaxNumber;
	int  m_iClientConnectionCheckTimeRound;

	int  m_iLevelExpTable[890];
 	CFish * m_pFish[MAXFISHS];
	CPotion * m_pPotionConfigList[MAXPOTIONTYPES];

	bool  m_bIsServerShutdowned;
	char  m_cShutDownCode;
	CMineral * m_pMineral[MAXMINERALS];

	int m_iMiddlelandMapIndex;
	int m_iAresdenMapIndex;
	int m_iElvineMapIndex;
	int m_iIstriaMapIndex;
	int m_iAstoriaMapIndex;
	Astoria m_astoria;
	Side m_astoriaBasePos[3];
	Side m_eventWinner[ET_MAX];
	CIni * m_eventsIni;

	bool	m_bIsApocalypseMode;	
	bool	m_bIsApocalypseGateOpen;
	
	bool	m_bHeldenianMode;
	DWORD	m_dwHeldenianGUID;
	int	m_iHeldenianType1Winner, m_iHeldenianType2Winner;
	int	m_iHeldenianType;
	int	m_iLastHeldenianType;
	int m_iHeldenianAresdenDead, m_iHeldenianElvineDead, m_iHeldenianAresdenKill, m_iHeldenianElvineKill, m_iHeldenianAresdenFlags, m_iHeldenianElvineFlags, 
		m_iHeldenianAresdenLeftTower, m_iHeldenianElvineLeftTower;
	int	m_iBtFieldMapIndex;
	int	m_iRampartMapIndex;
	int	m_iGodHMapIndex;

	int	 m_iMaxGMGMana;
	int m_iAresdenOccupyTiles;
	int m_iElvineOccupyTiles;
	int m_iCurMsgs, m_iMaxMsgs;

	DWORD m_dwCanFightzoneReserveTime ;

	int  m_iFightZoneReserve[MAXFIGHTZONE] ;

	int  m_iFightzoneNoForceRecall;

	struct ConfirmedIP 
	{
		char ip[20];
		DWORD timeReceived;
	};
	std::list<ConfirmedIP> confirmedIPs;

	struct RecentDisconnect
	{
		RecentDisconnect(char * pN, DWORD dT)
			{strcpy(playerName,pN); disconnectTimes[0] = dT; dcCount = 1; disconnectTimes[1] = disconnectTimes[2] = 0;}
		char playerName[12];
		DWORD disconnectTimes[3];
		int dcCount;
	};
	std::list<RecentDisconnect> m_recentDCs;

	struct {
		uint64 iFunds;
		uint64 iCrimes;
		uint64 iWins;
	} m_stCityStatus[MAXSIDES];

	int	  m_iStrategicStatus;

	XSocket * m_pSubLogSock[MAXSUBLOGSOCK];
	int   m_iSubLogSockInitIndex;
	bool  m_bIsSubLogSockAvailable[MAXSUBLOGSOCK];
	int	  m_iCurSubLogSockIndex;
	int   m_iSubLogSockFailCount;
	int   m_iSubLogSockActiveCount;
	int   m_iAutoRebootingCount;

	CBuildItem * m_pBuildItemList[MAXBUILDITEMS];
	CItem * m_pDupItemIDList[MAXDUPITEMID];

	char * m_pNoticementData;
	DWORD  m_dwNoticementDataSize;

	DWORD  m_dwMapSectorInfoTime;
	int    m_iMapSectorInfoUpdateCount;


		// Remember erazed clients
	struct {
		int iClientH;
		char m_cCharName[11];
		char m_cAccountName[11];
		char m_cAccountPassword[11];
		DWORD m_dwDeleteTime;
	} m_stOldClientList[MAXCLIENTS];

	bool   m_bIsCrusadeMode;
	struct {
		char cMapName[11];
		char cType;
		int  dX, dY;
	} m_stCrusadeStructures[MAXCRUSADESTRUCTURES];


	// 2 variables? hmm
	int m_iCollectedMana[MAXSIDES];
	int m_mana[MAXSIDES];
	// int m_iAresdenMana, m_iElvineMana;

	CTeleportLoc m_pGuildTeleportLoc[MAXGUILDS];
	//

	sBYTE  GSID;
	char  m_cGateServerStockMsg[MAXGATESERVERSTOCKMSGSIZE];
	int   m_iIndexGSS;

	struct {
		int iCrashedStructureNum;
		int iStructureDamageAmount;
		int iCasualties;
	} m_stMeteorStrikeResult;

	struct {
		char cType;
		char cSide;
		short sX, sY;
	} m_stMiddleCrusadeStructureInfo[MAXCRUSADESTRUCTURES];
	int m_iTotalMiddleCrusadeStructures;
 
		int m_iClientShortCut[MAXCLIENTS+1];

	int m_iNpcConstructionPoint[MAXNPCTYPES];
	DWORD m_dwCrusadeGUID;
	int   m_iCrusadeWinnerSide;   

	int   m_iPlayerMaxLevel;

	int	 m_iPrimaryDropRate, m_iSecondaryDropRate;

	int m_iEnemyKillAdjust;
	int m_sCharPointLimit;

		// Limit Checks
	short m_sCharStatLimit;
	short m_sCharSkillLimit;
	char m_cRepDropModifier;
	short m_sExpModifier;

	short m_sMaxPlayerLevel;
	short m_sRaidTimeMonday; 
	short m_sRaidTimeTuesday; 
	short m_sRaidTimeWednesday; 
	short m_sRaidTimeThursday; 
	short m_sRaidTimeFriday; 
	short m_sRaidTimeSaturday; 
	short m_sRaidTimeSunday; 

	int   m_iWorldMaxUser;

	short m_sForceRecallTime;
	short m_sSlateSuccessRate;

	void ReqCreateSlateHandler(int iClientH, char* pData);
	void SetSlateFlag(int iClientH, short sType, bool bFlag);

	int   m_iFinalShutdownCount;

	uint32  m_schedulesCnt;

	enum EventStatus{
		ES_ANNOUNCED_ONCE,
		ES_ANNOUNCED_TWICE,
		ES_ANNOUNCED_THRICE,
		ES_STARTED,
		ES_ENDED
	};
	struct {
		int iDay;
		int iHour;
		int iMinute;
		EventStatus evStatus;
		EventType evType;
		bool operator==(SYSTEMTIME sysTime)
		{
			return (iDay == sysTime.wDayOfWeek &&
				iHour == sysTime.wHour &&
				iMinute == sysTime.wMinute)
				? TRUE : FALSE;
		}
	} m_schedules[MAXSCHEDULE];


	struct {
		int iTotalMembers;
		int iIndex[MAXPARTYMEMBERS];
	} m_stPartyInfo[MAXPARTYNUM];

	CItem * m_pGold;

	XSocket * m_webSocket;
	char m_websiteAddr[61];
	char m_websiteScriptAddr[61];
	int m_websitePort;

	bool	m_bReceivedItemList;

	void _ClearExchangeStatus(int iClientH);	// previously private, who knows why
	void ShowClientMsg(int iClientH, char* pMsg);
	void SetAngel(short sOwnerH, char cOwnerType, int iStatus, bool notify = TRUE);
	void GetAngelHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void GetDKItemHandler(int iClientH, char * pData, DWORD dwMsgSize);
	void AdminOrder_GoTo(int iClientH, char* pData, DWORD dwMsgSize);
	void AdminOrder_Pushplayer(int iClientH, char * pData, DWORD dwMsgSize);

private:
	int __iSearchForQuest(int iClientH, int iWho, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iTalkToNpcResult_Cityhall(int iClientH, int * pQuestType, int * pMode, int * pRewardType, int * pRewardAmount, int * pContribution, char * pTargetName, int * pTargetType, int * pTargetCount, int * pX, int * pY, int * pRange);
	int _iGetItemSpaceLeft(int iClientH);

};

#endif // !defined(AFX_GAME_H__C3D29FC5_755B_11D2_A8E6_00001C7030A6__INCLUDED_)
