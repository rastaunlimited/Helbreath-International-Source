// Client.cpp: implementation of the CClient class.
//
//////////////////////////////////////////////////////////////////////

#include "..\HG.h"
#include "combat.h"
#include "..\..\shared\NetMessages.h"

extern class CGame *   g_game;
extern char            g_cTxt[512];
extern class CClient ** g_clientList;
extern class CNpc **	g_npcList;
extern class CMap	**	g_mapList;

extern int * g_skillSSNpoint;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CClient::CClient(HWND hWnd, int clientH)
{
	register int i;

	m_handle = clientH;
	m_ownerType = OWNERTYPE_PLAYER;
	m_bIsBeingResurrected = FALSE;

	m_pXSock = NULL;

	ZeroMemory(m_cProfile, sizeof(m_cProfile));
	strcpy(m_cProfile, "__________");

	ZeroMemory(m_cCharName, sizeof(m_cCharName));
	ZeroMemory(m_cAccountName, sizeof(m_cAccountName));
	ZeroMemory(m_cAccountPassword, sizeof(m_cAccountPassword));

	ZeroMemory(m_cGuildName, sizeof(m_cGuildName));
	ZeroMemory(m_cLocation, sizeof(m_cLocation));
	ZeroMemory(m_cMapName, sizeof(m_cMapName));

	strcpy(m_cLocation, "NONE");
	m_iGuildRank = -1;
	m_iGuildGUID = -1;

	m_bIsInitComplete = FALSE;

	m_dwCharID = 0;


	//m_iHitRatio_ItemEffect_SM = 0;
	//m_iHitRatio_ItemEffect_L  = 0;

	m_iEnemyKillCount = 0;
	m_iPKCount = 0;
	m_iRewardGold = 0;
	m_iCurWeightLoad = 0;

	m_bIsSafeAttackMode  = FALSE;


	for (i = 0; i < MAXITEMEQUIPPOS; i++) 
		m_sItemEquipmentStatus[i] = -1;


	for (i = 0; i < MAXITEMS; i++) {
		m_pItemList[i]       = NULL;
		m_ItemPosList[i].x   = 40;
		m_ItemPosList[i].y   = 30;
		m_bIsItemEquipped[i] = FALSE;
	}
	m_cArrowIndex = -1;
		for (i = 0; i < MAXBANKITEMS; i++) {
		m_pItemInBankList[i] = NULL;
	}


	for (i = 0; i < MAXMAGICTYPE; i++)
		m_cMagicMastery[i] = NULL;

	for (i = 0; i < MAXSKILLTYPE; i++)
		m_cSkillMastery[i] = NULL;

	for (i = 0; i < MAXSKILLTYPE; i++) {
		m_bSkillUsingStatus[i] = FALSE;
		m_iSkillUsingTimeID[i] = NULL;
	}

	// testcode
	m_cMapIndex = -1;
	m_sX = -1;
	m_sY = -1;
	m_cDir = 5;
	m_sType   = 0;
	m_sAppr1  = 0;
	m_sAppr2  = 0;
	m_sAppr3  = 0;
	m_sAppr4  = 0;
	m_iApprColor = 0; 

	m_cSex  = NONE;
	m_cSkin = 0;
	m_cHairStyle  = 0;
	m_cHairColor  = 0;
	m_cUnderwear  = 0;

	m_cAttackDiceThrow_SM = 0;
	m_cAttackDiceRange_SM = 0;
	m_cAttackDiceThrow_L = 0;
	m_cAttackDiceRange_L = 0;
	m_cAttackBonus_SM    = 0;
	m_cAttackBonus_L     = 0;

	m_side = 0;

	m_iHitRatio = 0;
	m_iDefenseRatio = 0;

	for (i = 0; i < MAXITEMEQUIPPOS; i++) m_iDamageAbsorption_Armor[i]  = 0;
	m_iDamageAbsorption_Shield = 0;


	m_iHPstock = 0;
	m_iHPStatic_stock = 0 ;

	for (i = 0; i < MAXMAGICEFFECTS; i++) 
		m_cMagicEffectStatus[i]	= 0;

	m_iWhisperPlayerIndex = -1;
	ZeroMemory(m_cWhisperPlayerName, sizeof(m_cWhisperPlayerName));

	m_iHungerStatus  = 100;  

	m_bIsWarLocation = FALSE;

	m_bIsPoisoned    = FALSE;
	m_iPoisonLevel   = NULL;

	m_iAdminUserLevel  = 0;
	m_GMFlags = 0;

	m_reputation          = 0;
	m_iTimeLeft_ShutUp = 0;
	m_iTimeLeft_Rating = 0;
	m_iTimeLeft_ForceRecall  = 0;
	m_iTimeLeft_FirmStamina = 0;
	m_dwLogoutHackCheck = 0;
	m_lastDamageTime = 0;

	m_bIsOnServerChange  = FALSE;

	m_iExpStock = 0;

	m_iAllocatedFish = NULL;
	m_iFishChance    = 0;

	ZeroMemory(m_cIPaddress, sizeof(m_cIPaddress)); 
	m_bIsOnWaitingProcess = FALSE;

	m_iSuperAttackLeft  = 0;
	m_iSuperAttackCount = 0;

	//m_sUsingWeaponSkill = SKILL_HANDATTACK; 
	m_iMPSaveRatio   = 0;
	m_iAddResistMagic  = 0;
	m_iAddPhysicalDamage = 0;
	m_iAddMagicalDamage  = 0;
	m_addMagicDmgPct  = 0;
	m_bIsLuckyEffect     = FALSE;
	m_iSideEffect_MaxHPdown = 0;

	m_iAddAbsAir   = 0;
	m_iAddAbsEarth = 0;
	m_iAddAbsFire  = 0;
	m_iAddAbsWater = 0;

	m_iComboAttackCount = 0;
	m_iDownSkillIndex   = -1;

	m_iMagicDamageSaveItemIndex = -1;

	m_sCharIDnum1 = m_sCharIDnum2 = m_sCharIDnum3 = 0;

	m_partyCoordSteps = 0;
	m_partyHpCount = 0;
	m_partyMpCount = 0;
	m_iPartyRank = -1; 
	m_iPartyMemberCount = 0;
	m_iPartyGUID        = 0;

	for (i = 0; i < MAXPARTYMEMBERS; i++) {
		m_stPartyMemberName[i].iIndex = 0;
		ZeroMemory(m_stPartyMemberName[i].cName, sizeof(m_stPartyMemberName[i].cName));
	}

	m_iAbuseCount     = 0;
	m_bIsBWMonitor    = FALSE;
	


    m_iFightZoneTicketNumber =	m_iFightzoneNumber = m_iReserveTime = 0 ;            

	m_iPenaltyBlockYear = m_iPenaltyBlockMonth = m_iPenaltyBlockDay = 0; 

	m_isExchangeMode = FALSE;
	m_isExchangeConfirm = FALSE;
	m_exchangeH = NULL;
	m_exchangeCount = 0;
	
	for(i = 0; i < 4; i++){
		ZeroMemory(m_exchangeItems[i].itemName, sizeof(m_exchangeItems[i].itemName));
		m_exchangeItems[i].itemAmount = 0;
		m_exchangeItems[i].itemIndex  = -1;		
	}	

	m_iQuest		 = NULL; 
	m_iQuestID       = NULL; // QuestID
	m_iAskedQuest	 = NULL; 
	m_iCurQuestCount = NULL; 
	m_iQuestRewardType	 = NULL; 
	m_iQuestRewardAmount = NULL; 

	m_iContribution = NULL;
	m_bQuestMatchFlag_Loc = FALSE;  
	m_bIsQuestCompleted   = FALSE;

	m_bIsNeutral      = FALSE;
	m_bIsObserverMode = FALSE;


	m_iSpecialEventID = 200081;

	m_iSpecialWeaponEffectType  = 0;
	m_iSpecialWeaponEffectValue = 0;
	m_iAddHP = m_iAddSP = m_iAddMP = 0; 
	m_iAddAR = m_iAddPR = m_iAddDR = 0;
	m_iAddAbsPD = m_iAddAbsMD = 0;
	m_iAddCD = m_iAddExp = m_iAddGold = 0;

	m_iSpecialAbilityTime = SPECABLTYTIMESEC;
	m_iSpecialAbilityType = NULL;
	m_bIsSpecialAbilityEnabled = FALSE;
	m_specialAbilityLastSec   = 0;

	m_iSpecialAbilityEquipPos  = 0;

	m_iMoveMsgRecvCount   = 0;
	m_iAttackMsgRecvCount = 0;
	m_iRunMsgRecvCount    = 0;
	m_iSkillMsgRecvCount  = 0;
 
	m_iAlterItemDropIndex = -1;

	m_iAutoExpAmount = 0;
	m_iWarContribution = 0;
	
	// Snoopy: Anti-Hack based on connection check by client.
	m_iConnectionCheck = 0;
	dwTimeConnectionCheck = 0;
	dwEventTimeConnectionCheck = 0;	
	for (i = 0; i < 11; i++) m_cMsgCount[i] = 0;

	m_dwMoveLAT = m_dwRunLAT = m_dwAttackLAT = 0;

	m_dwInitCCTimeRcv = 0;
	m_dwInitCCTime = 0;

	ZeroMemory(m_cLockedMapName, sizeof(m_cLockedMapName));
	strcpy(m_cLockedMapName, "NONE");
	m_iLockedMapTime   = NULL;
	m_iDeadPenaltyTime = NULL;

	m_iCrusadeDuty  = NULL;
	m_dwCrusadeGUID = NULL;

	for (i = 0; i < MAXCRUSADESTRUCTURES; i++) {
		m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
	}
	m_iCSIsendPoint = NULL;

	m_bIsSendingMapStatus = FALSE;
	ZeroMemory(m_cSendingMapName, sizeof(m_cSendingMapName));

	m_iConstructionPoint = NULL;

	ZeroMemory(m_cConstructMapName, sizeof(m_cConstructMapName));
	m_iConstructLocX = m_iConstructLocY = -1;

	m_dwFightzoneDeadTime = NULL;

	m_iPartyID = NULL;
	m_iPartyStatus = PARTYSTATUS_NULL;

	m_iReqJoinPartyClientH = NULL;
	ZeroMemory(m_cReqJoinPartyName, sizeof(m_cReqJoinPartyName));

	m_dwLastActionTime = NULL;
	m_bIsCheckingWhisperPlayer = FALSE;

	m_hasPrecasted = false;

	m_bIsBankModified = FALSE ;

	m_iGizonItemUpgradeLeft = 0;

	m_dwAttackFreqTime = m_dwMagicFreqTime = m_dwMoveFreqTime = NULL; 
	m_bIsMoveBlocked = FALSE; 
	m_bIsAttackModeChange = FALSE; 
	m_iIsOnTown = FALSE;
	m_bIsOnShop = FALSE ; 
	m_bIsOnTower = FALSE ; 
	m_bIsOnWarehouse = FALSE ; 
	m_dwWarmEffectTime = NULL; 
	m_bIsInBuilding = FALSE ;

	_angelStr = _angelMag = _angelInt = _angelDex = 0;
}

CClient::~CClient()
{
 int i;

	if (m_pXSock != NULL) delete m_pXSock;
	for (i = 0; i < MAXITEMS; i++)
	if (m_pItemList[i] != NULL) {
		delete m_pItemList[i];
		m_pItemList[i] = NULL;
	}
}

void CClient::SetStr(int str, bool check) 
{
	_str = str;
	if(check)
	{
		if(m_iHP > GetMaxHP())
		{
			m_iHP = GetMaxHP();
			g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_HP, NULL, NULL, NULL, NULL);
		}
		if(m_iSP > GetMaxSP())
		{
			m_iSP = GetMaxSP();
			g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_SP, NULL, NULL, NULL, NULL);
		}
	}
}

void CClient::SetMag(int mag)
{
	_mag = mag;
	if(m_iMP > GetMaxMP())
	{
		m_iMP = GetMaxMP();
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_MP, NULL, NULL, NULL, NULL);
	}
}

void CClient::SetInt(int __int, bool check)
{
	_int = __int;
	if(check)
	{
		if(m_iMP > GetMaxMP())
		{
			m_iMP = GetMaxMP();
			g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_MP, NULL, NULL, NULL, NULL);
		}
	}
}

void CClient::SetDex(int dex)
{
	_dex = dex;
}

void CClient::SetAngelStr(int str)
{
	_angelStr = str;

	if(m_iHP > GetMaxHP())
	{
		m_iHP = GetMaxHP();
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_HP, NULL, NULL, NULL, NULL);
	}
	if(m_iSP > GetMaxSP())
	{
		m_iSP = GetMaxSP();
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_SP, NULL, NULL, NULL, NULL);
	}
/*	Done client-side.
	for (short sItemIndex = 0; sItemIndex < MAXITEMS; sItemIndex++)
		if  ((m_pItemList[sItemIndex] != NULL) && 
			(m_bIsItemEquipped[sItemIndex] == TRUE))
		{
			if(m_pItemList[sItemIndex]->m_wWeight/100 > GetStr())
				g_game->ReleaseItemHandler(m_handle, sItemIndex, TRUE);
		}*/
}
void CClient::SetAngelDex(int dex)
{
	_angelDex = dex;
}
void CClient::SetAngelInt(int __int)
{
	_angelInt = __int;
	if(m_iMP > GetMaxMP())
	{
		m_iMP = GetMaxMP();
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_MP, NULL, NULL, NULL, NULL);
	}
}
void CClient::SetAngelMag(int mag)
{
	_angelMag = mag ;
	if(m_iMP > GetMaxMP())
	{
		m_iMP = GetMaxMP();
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_MP, NULL, NULL, NULL, NULL);
	}
}

bool CClient::bCreateNewParty()
{
 int i;

	if (m_iPartyRank != -1) return FALSE;

	m_iPartyRank = 0;
	m_iPartyMemberCount = 0;
	m_iPartyGUID = (rand() % 999999) + timeGetTime();

	for (i = 0; i < MAXPARTYMEMBERS; i++) {
		m_stPartyMemberName[i].iIndex = 0;
		ZeroMemory(m_stPartyMemberName[i].cName, sizeof(m_stPartyMemberName[i].cName));
	}

	return TRUE;
}


bool CClient::CheckTotalSkillMasteryPoints(int iSkill)
{
	register int i;
	int iRemainPoint, iTotalPoints, iWeaponIndex, iDownSkillSSN, iDownPoint;
	short sDownSkillIndex;

	iTotalPoints = 0;
	for (i = 0; i <	MAXSKILLTYPE; i++) 
		iTotalPoints += m_cSkillMastery[i];

	iRemainPoint = iTotalPoints - MAXSKILLPOINTS;

	if (iRemainPoint > 0) {
		while (iRemainPoint > 0) {
			sDownSkillIndex = -1; 
			if (m_iDownSkillIndex != -1) {
				if (m_cSkillMastery[m_iDownSkillIndex] > 0) {
					sDownSkillIndex = m_iDownSkillIndex;
				}
				else {
					iDownSkillSSN = 99999999;
					for (i = 0; i < MAXSKILLTYPE; i++)
						if ((m_cSkillMastery[i] >= 21) && (i != iSkill) && 
							(m_iSkillSSN[i] <= iDownSkillSSN)) {
								iDownSkillSSN = m_iSkillSSN[i];
								sDownSkillIndex = i;
						}
				}
			}

			if (sDownSkillIndex != -1) {

				if (m_cSkillMastery[sDownSkillIndex] <= 20)
					iDownPoint = m_cSkillMastery[sDownSkillIndex];
				else iDownPoint = 1;

				m_cSkillMastery[sDownSkillIndex] -= iDownPoint;
				m_iSkillSSN[sDownSkillIndex] = g_skillSSNpoint[m_cSkillMastery[sDownSkillIndex]+1] - 1;
				iRemainPoint -= iDownPoint;

				if (m_sItemEquipmentStatus[ EQUIPPOS_TWOHAND ] != -1) {
					iWeaponIndex = m_sItemEquipmentStatus[ EQUIPPOS_TWOHAND ];
					if (m_pItemList[iWeaponIndex]->m_sRelatedSkill == sDownSkillIndex) {
						m_iHitRatio -= iDownPoint;
						if (m_iHitRatio < 0) m_iHitRatio = 0;
					}
				}

				if (m_sItemEquipmentStatus[ EQUIPPOS_RHAND ] != -1) {
					iWeaponIndex = m_sItemEquipmentStatus[ EQUIPPOS_RHAND ];
					if (m_pItemList[iWeaponIndex]->m_sRelatedSkill == sDownSkillIndex) {
						m_iHitRatio -= iDownPoint;
						if (m_iHitRatio < 0) m_iHitRatio = 0;
					}
				}
				g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_SKILL, sDownSkillIndex, m_cSkillMastery[sDownSkillIndex], NULL, NULL);
			}
			else {
				return FALSE;
			}
		}
		return TRUE;
	}

	return FALSE;
}

void CClient::ValidateSkills(bool logInvalidSkills)
{
	if(IsGM()) return;

	int invalidSkills = 0;
	char logMessage[100];
	for (int skillIndex = 0; skillIndex < MAXSKILLTYPE; skillIndex++)
	{	
		switch (skillIndex) {
		case SKILL_MINING:  
		case SKILL_MANUFACTURING:
			if (m_cSkillMastery[skillIndex] > (GetStr() * 2)) 
			{	
				invalidSkills += m_cSkillMastery[skillIndex] - (GetStr() * 2);
				m_cSkillMastery[skillIndex] = GetStr() * 2;
				m_iSkillSSN[skillIndex] = 0;
				Notify(NULL, NOTIFY_SKILL, skillIndex, m_cSkillMastery[skillIndex], NULL, NULL);
			}
			break;

		case SKILL_PRAYER:
case SKILL_CRAFTING:
			case SKILL_PRETENDCORPSE:
			case SKILL_AGILITY:
				case SKILL_FISHING:
			if (m_cSkillMastery[skillIndex] > (m_iLevel * 2)) 
			{	
				invalidSkills += m_cSkillMastery[skillIndex] - (m_iLevel * 2);
				m_cSkillMastery[skillIndex] = m_iLevel * 2;
				m_iSkillSSN[skillIndex] = 0;
				Notify(NULL, NOTIFY_SKILL, skillIndex, m_cSkillMastery[skillIndex], NULL, NULL);
			}
			break;

		////case SKILL_MAGIC:
		////case SKILL_STAFF:
		////	if (m_cSkillMastery[skillIndex] > (GetMag() * 2))
		////	{ 	
		////		invalidSkills += m_cSkillMastery[skillIndex] - (GetMag() * 2);
		////		m_cSkillMastery[skillIndex] = GetMag() * 2;
		////		m_iSkillSSN[skillIndex] = 0;
		////		Notify(NULL, NOTIFY_SKILL, skillIndex, m_cSkillMastery[skillIndex], NULL, NULL);
		////	}
		////	break;

	/*	case SKILL_FISHING:
			if (m_cSkillMastery[skillIndex] > (GetDex() * 2)) 
			{	
				invalidSkills += m_cSkillMastery[skillIndex] - (GetDex() * 2);
				m_cSkillMastery[skillIndex] = GetDex() * 2;
				m_iSkillSSN[skillIndex] = 0;
				Notify(NULL, NOTIFY_SKILL, skillIndex, m_cSkillMastery[skillIndex], NULL, NULL);
			}
			break;*/

		case SKILL_ALCHEMY:
		case SKILL_FARMING:
		
			if (m_cSkillMastery[skillIndex] > (GetInt() * 2)) 
			{	
				invalidSkills += m_cSkillMastery[skillIndex] - (GetInt() * 2);
				m_cSkillMastery[skillIndex] = GetInt() * 2;
				m_iSkillSSN[skillIndex] = 0;
				Notify(NULL, NOTIFY_SKILL, skillIndex, m_cSkillMastery[skillIndex], NULL, NULL);
			}
			break;

		//case SKILL_POISONRES:
		//	if (m_cSkillMastery[skillIndex] > (m_iVit * 2)) 
		//	{	
		//		invalidSkills += m_cSkillMastery[skillIndex] - (m_iVit * 2);
		//		m_cSkillMastery[skillIndex] = m_iVit * 2;
		//		m_iSkillSSN[skillIndex] = 0;
		//		Notify(NULL, NOTIFY_SKILL, skillIndex, m_cSkillMastery[skillIndex], NULL, NULL);
		//	}
		//	break;
		default:
			m_iSkillSSN[skillIndex] = 0;
			break;
		}
	}

	if(logInvalidSkills && (invalidSkills > 0))
	{
		wsprintf(logMessage, "PC(%s) A skill was too high, reduced by (%d) points", m_cCharName, invalidSkills);
		PutLogList(logMessage);
	}
}

int CClient::GetPlayerRelationship(int iOpponentH) const
{
	int iRet;

	if (m_bIsInitComplete == FALSE) return 0;

	if (g_clientList[iOpponentH] == NULL) return 0;
	if (g_clientList[iOpponentH]->m_bIsInitComplete == FALSE) return 0;

	iRet = 0;

	if (m_iPKCount != 0) {
		if ((m_side == g_clientList[iOpponentH]->m_side) &&
			(m_side != NEUTRAL) && (g_clientList[iOpponentH]->m_side != NEUTRAL))
			iRet = 7;
		else iRet = 2; 
	}
	else if (g_clientList[iOpponentH]->m_iPKCount != 0) {
		if ((m_side == g_clientList[iOpponentH]->m_side) &&
			(m_side != NEUTRAL) && (g_clientList[iOpponentH]->m_side != NEUTRAL))
			iRet = 6;
		else iRet = 2;
	}
	else {
		if (m_side != g_clientList[iOpponentH]->m_side) {
			if ((m_side != NEUTRAL) && (g_clientList[iOpponentH]->m_side != NEUTRAL)) {
				// (Traveler)
				iRet = 2;
			}
			else {
				iRet = 0;
			}
		}
		else {
			if ((memcmp(m_cGuildName, g_clientList[iOpponentH]->m_cGuildName, 20) == 0) &&
				(memcmp(m_cGuildName, "NONE", 4) != 0) ) {
					if (g_clientList[iOpponentH]->m_iGuildRank == 0)
						iRet = 5;
					else iRet = 3;
			}
			else 
				if ((m_side == g_clientList[iOpponentH]->m_side) &&
					(memcmp(m_cGuildName, "NONE", 4) != 0) &&
					(memcmp(g_clientList[iOpponentH]->m_cGuildName, "NONE", 4) != 0) &&
					(memcmp(m_cGuildName, g_clientList[iOpponentH]->m_cGuildName, 20) != 0)) {
						iRet = 4;
				}
				else iRet = 1;
		}
	}

	return iRet;
}
int CClient::GetMaxHP() const
{
	int iRet;

	iRet = m_iVit*3 + m_iLevel*2 + (GetStr())/2;
	
	if (m_iSideEffect_MaxHPdown != 0)
		iRet = iRet - (iRet/m_iSideEffect_MaxHPdown);

	return iRet;
}

int CClient::GetMaxMP() const
{
	int iRet;

	iRet = (2*(GetMag()) ) + (2*m_iLevel) + ((GetInt())/2);

	return iRet;
}

int CClient::GetMaxSP() const
{
	int iRet;

	iRet = (2*GetStr()) + (2*m_iLevel);

	return iRet;
}

void CClient::AddHP(long hp)
{
	int maxHP = GetMaxHP();
	m_iHP += hp; 
	if (m_iHP > maxHP) m_iHP = maxHP;
	g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_HP, NULL, NULL, NULL, NULL);
}

void CClient::KilledHandler(int iAttackerH, char cAttackerType, short sDamage)
{
	char  * cp, cAttackerName[21], cData[120];
	short sAttackerWeapon;
	int   * ip, i, iExH;
	bool  bIsSAattacked = FALSE;

	if (m_bIsInitComplete == FALSE) return;
	if (m_bIsKilled == TRUE) return;

	if (memcmp(g_mapList[m_cMapIndex]->m_cName, "fight", 5) == 0) {
		m_dwFightzoneDeadTime = timeGetTime();
		wsprintf(g_cTxt, "Fightzone Dead Time: %d", m_dwFightzoneDeadTime);
		PutLogList(g_cTxt);
	}

	m_bIsKilled = TRUE;
	m_iHP = 0;

	if (m_isExchangeMode == TRUE) {
		iExH = m_exchangeH;
		g_game->_ClearExchangeStatus(iExH);
		g_game->_ClearExchangeStatus(m_handle);
	}

	g_game->RemoveFromTarget(m_handle, OWNERTYPE_PLAYER);

	ZeroMemory(cAttackerName, sizeof(cAttackerName));
	switch (cAttackerType) {
	case OWNERTYPE_PLAYER_INDIRECT:
	case OWNERTYPE_PLAYER:
		if (g_clientList[iAttackerH] != NULL)
			memcpy(cAttackerName, g_clientList[iAttackerH]->m_cCharName, 10);
		break;
	case OWNERTYPE_NPC:
		if (g_npcList[iAttackerH] != NULL)
			memcpy(cAttackerName, g_npcList[iAttackerH]->m_cNpcName, 20);
		break ;
	default:
		break;
	}

	g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_KILLED, NULL, NULL, NULL, cAttackerName);
	if (cAttackerType == OWNERTYPE_PLAYER) {
		sAttackerWeapon = ((g_clientList[iAttackerH]->m_sAppr2 & 0x0FF0) >> 4);
	}
	else sAttackerWeapon = 1;
	g_game->SendEventToNearClient_TypeA(m_handle, OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, OBJECTDYING, sDamage, sAttackerWeapon, NULL);
	g_mapList[m_cMapIndex]->ClearOwner(/*12,*/ m_handle, OWNERTYPE_PLAYER, m_sX, m_sY);
	g_mapList[m_cMapIndex]->SetDeadOwner(m_handle, OWNERTYPE_PLAYER, m_sX, m_sY);

	int itemInd;
	if(g_game->m_astoria.get() && g_game->m_astoria->IsCapture() && (itemInd = HasItem(ITEM_RELIC)))
	{
		g_game->DropItemHandler(m_handle, itemInd, 1, m_pItemList[itemInd]->m_cName, FALSE);
	}

	if (g_mapList[m_cMapIndex]->m_cType == MAPTYPE_NOPENALTY_NOREWARD) return;

	if (cAttackerType == OWNERTYPE_PLAYER) {
		switch (g_clientList[iAttackerH]->m_iSpecialAbilityType) {
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
			bIsSAattacked = TRUE;
			break;
		}

		if (iAttackerH == m_handle) return;
		if (IsNeutral()) {
			if (m_iPKCount == 0) {

			//	g_clientList[iAttackerH]->ApplyPKPenalty(m_handle);
				g_game->EnemyKillRewardHandler(iAttackerH, m_handle);
			}
			else {
				g_game->PK_KillRewardHandler(iAttackerH, m_handle);
			}
		} 
		else {
			if (g_clientList[iAttackerH]->IsNeutral()) {
				if (m_iPKCount == 0) {
					//	g_clientList[iAttackerH]->ApplyPKPenalty(m_handle);
					g_game->EnemyKillRewardHandler(iAttackerH, m_handle);
				}
				else {
					g_clientList[iAttackerH]->ApplyPKPenalty(m_handle);
				}
			}
			else {
				if(g_game->m_astoria.get())
					g_game->m_astoria->PlayerKill(g_clientList[iAttackerH], this);
				
				if (g_game->m_bHeldenianMode && g_mapList[m_cMapIndex]->m_bIsHeldenianMap) 
					g_game->HeldenianPlayerKill(g_clientList[iAttackerH], this);

				if (m_side == g_clientList[iAttackerH]->m_side) {
					if (m_iPKCount == 0) {
						g_clientList[iAttackerH]->ApplyPKPenalty(m_handle);
					}
					else {
						g_game->PK_KillRewardHandler(iAttackerH, m_handle);
					}
				}
				else {
					g_game->EnemyKillRewardHandler(iAttackerH, m_handle);
				}
			}
		}

		if (m_iPKCount == 0) {
			// Innocent
			if (g_clientList[iAttackerH]->IsNeutral()) {
			}
			else {
				if (m_side == g_clientList[iAttackerH]->m_side) {
				}
				else {
					ApplyCombatKilledPenalty(2, bIsSAattacked);
				}
			}
		}
		else if ((m_iPKCount >= 1) && (m_iPKCount <= 3)) {
			// Criminal 
			ApplyCombatKilledPenalty(3, bIsSAattacked,TRUE);
		}
		else if ((m_iPKCount >= 4) && (m_iPKCount <= 11)) {
			// Murderer 
			ApplyCombatKilledPenalty(6, bIsSAattacked,TRUE);
		}
		else if (m_iPKCount >= 12) {
			// Slaughterer 
			ApplyCombatKilledPenalty(12, bIsSAattacked,TRUE);
		}
	}
	else if (cAttackerType == OWNERTYPE_NPC) {

		g_game->_bPKLog(PKLOG_BYNPC,(int) -1,m_handle,cAttackerName) ;

		if (m_iPKCount == 0) {
			// Innocent
			ApplyCombatKilledPenalty(1, bIsSAattacked,TRUE);
		}
		else if ((m_iPKCount >= 1) && (m_iPKCount <= 3)) {
			// Criminal 
			ApplyCombatKilledPenalty(3, bIsSAattacked , TRUE);
		}
		else if ((m_iPKCount >= 4) && (m_iPKCount <= 11)) {
			// Murderer 
			ApplyCombatKilledPenalty(6, bIsSAattacked , TRUE);
		}
		else if (m_iPKCount >= 12) {
			// Slaughterer 
			ApplyCombatKilledPenalty(12, bIsSAattacked , TRUE);
		}

		if (g_npcList[iAttackerH]->m_iGuildGUID != NULL) {

			if (g_npcList[iAttackerH]->m_side != m_side) {
				for (i = 1; i < MAXCLIENTS; i++)
					if ((g_clientList[i] != NULL) && (g_clientList[i]->m_iGuildGUID == g_npcList[iAttackerH]->m_iGuildGUID) &&
						(g_clientList[i]->m_iCrusadeDuty == 3)) {
							g_clientList[i]->m_iConstructionPoint += (m_iLevel / 2);

							if (g_clientList[i]->m_iConstructionPoint > MAXCONSTRUCTIONPOINT) 
								g_clientList[i]->m_iConstructionPoint = MAXCONSTRUCTIONPOINT;

							//testcode
							wsprintf(g_cTxt, "Enemy Player Killed by Npc! Construction +%d", (m_iLevel / 2));
							PutLogList(g_cTxt);
							g_game->SendNotifyMsg(NULL, i, NOTIFY_CONSTRUCTIONPOINT, g_clientList[i]->m_iConstructionPoint, g_clientList[i]->m_iWarContribution, NULL, NULL);
							return;
					}

					ZeroMemory(cData, sizeof(cData));
					cp = (char *)cData;
					*cp = GSM_CONSTRUCTIONPOINT;
					cp++;
					ip = (int*)cp;
					*ip = g_npcList[iAttackerH]->m_iGuildGUID;
					cp += 4;
					ip = (int*)cp;
					*ip = (m_iLevel / 2);
					cp += 4;
					g_game->bStockMsgToGateServer(cData, 9);
			}
		}
	}
	else if (cAttackerType == OWNERTYPE_PLAYER_INDIRECT) {
		g_game->_bPKLog(PKLOG_BYOTHER,(int) -1,m_handle,NULL) ;
		// m_iExp -= dice(1, 50);
		// if (m_iExp < 0) m_iExp = 0;

		// g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_EXP, NULL, NULL, NULL, NULL);
	}
}

void CClient::ApplyCombatKilledPenalty(char cPenaltyLevel, bool bIsSAattacked, bool bItemDrop)
{  
	int iExp;

	if (m_bIsInitComplete == FALSE) return;

	if (g_game->m_bIsCrusadeMode) 
	{
		DecPKCount();
		return;
	}
	else if (g_game->m_bIsApocalypseMode && g_mapList[m_cMapIndex]->m_bIsApocalypseMap) 
	{
		DecPKCount();
		return;
	}
	else if (g_game->m_bHeldenianMode && g_mapList[m_cMapIndex]->m_bIsHeldenianMap) 
	{
		DecPKCount();
		return;
	}
	else if(g_game->m_astoria.get() && m_cMapIndex == g_game->m_iAstoriaMapIndex)
	{
		DecPKCount();	
		return;
	}
	else {
		DecPKCount();

		iExp = dice(1, (5*cPenaltyLevel*m_iLevel));

		if (m_bIsNeutral == TRUE) iExp = iExp / 3;

		// if (m_iLevel == m_iPlayerMaxLevel) iExp = 0;

		m_iExp -= iExp;
		if (m_iExp < 0) m_iExp = 0;

		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_EXP, NULL, NULL, NULL, NULL);

		if (m_bIsNeutral != TRUE) {
#ifdef ITEMDROP
			if (m_iLevel < 80) {
				cPenaltyLevel--;
				if (cPenaltyLevel <= 0) cPenaltyLevel = 1;
			}
			PenaltyItemDrop(cPenaltyLevel, bIsSAattacked,bItemDrop); 
#else
			if (m_iLevel < 80) {
				cPenaltyLevel--;
				if (cPenaltyLevel <= 0) cPenaltyLevel = 1;
			}
			PenaltyItemDrop(cPenaltyLevel, bIsSAattacked);
#endif
		}
	}
}


void CClient::PenaltyItemDrop(int iTotal, bool bIsSAattacked , bool bItemDrop)
{
	register int i, j, iRemainItem;
	char cItemIndexList[MAXITEMS], cItemIndex;

	if (m_bIsInitComplete == FALSE) return;

	if ((m_iAlterItemDropIndex != -1) && (m_pItemList[m_iAlterItemDropIndex] != NULL)) {
		// Testcode
		if (m_pItemList[m_iAlterItemDropIndex]->m_sItemEffectType == ITEMEFFECTTYPE_ALTERITEMDROP) {
			if (m_pItemList[m_iAlterItemDropIndex]->m_wCurLifeSpan > 0)
				m_pItemList[m_iAlterItemDropIndex]->m_wCurLifeSpan--;

			g_game->DropItemHandler(m_handle, m_iAlterItemDropIndex, -1, m_pItemList[m_iAlterItemDropIndex]->m_cName);

			m_iAlterItemDropIndex = -1;
		}
		else {
			// testcode
			PutLogFileList("Alter Drop Item Index Error1");
			for (i = 0; i < MAXITEMS; i++) 
				if ((m_pItemList[i] != NULL) && (m_pItemList[i]->m_sItemEffectType == ITEMEFFECTTYPE_ALTERITEMDROP)) {
					m_iAlterItemDropIndex = i;
					if (m_pItemList[m_iAlterItemDropIndex]->m_wCurLifeSpan > 0)
						m_pItemList[m_iAlterItemDropIndex]->m_wCurLifeSpan--;

					g_game->DropItemHandler(m_handle, m_iAlterItemDropIndex, -1, m_pItemList[m_iAlterItemDropIndex]->m_cName);
					m_iAlterItemDropIndex = -1;
					return;
				}

				goto PID_DROP;
		}
		return;
	}

PID_DROP:;

	for (i = 1; i <= iTotal; i++) {
		iRemainItem = 0;
		ZeroMemory(cItemIndexList, sizeof(cItemIndexList));

#ifdef ITEMDROP
		if (bItemDrop)
		{
			for (j = 0; j < MAXITEMS; j++) 
				if (m_pItemList[j] != NULL )
				{
					cItemIndexList[iRemainItem] = j;
					iRemainItem++;
				}
		}
		else 
		{
			//
			for (j = 0; j < MAXITEMS; j++) 
				if (m_pItemList[j] != NULL 
					&& ( (m_pItemList[j]->m_cItemType == ITEMTYPE_CONSUME) 
					|| (m_pItemList[j]->m_cItemType == ITEMTYPE_EAT) ))
				{
					cItemIndexList[iRemainItem] = j;
					iRemainItem++;
				}
		}
#else
		for (j = 0; j < MAXITEMS; j++) 
			if (m_pItemList[j] != NULL )
			{
				cItemIndexList[iRemainItem] = j;
				iRemainItem++;
			}
#endif
			if (iRemainItem == 0) return;
			cItemIndex = cItemIndexList[ dice(1, iRemainItem) - 1 ];

			if ((m_pItemList[cItemIndex]->m_sTouchEffectType != 0) &&
				(m_pItemList[cItemIndex]->m_sTouchEffectValue1 == m_sCharIDnum1) &&
				(m_pItemList[cItemIndex]->m_sTouchEffectValue2 == m_sCharIDnum2) &&
				(m_pItemList[cItemIndex]->m_sTouchEffectValue3 == m_sCharIDnum3)) {
			}
			else if (((m_pItemList[cItemIndex]->m_sItemEffectType == ITEMEFFECTTYPE_ATTACK_SPECABLTY) ||
				(m_pItemList[cItemIndex]->m_sItemEffectType == ITEMEFFECTTYPE_DEFENSE_SPECABLTY)) &&
				(bIsSAattacked == FALSE)) {
			}
			else if ((m_bIsLuckyEffect == TRUE) && (dice(1,10) == 5)) {
			}
			else g_game->DropItemHandler(m_handle, cItemIndex, -1, m_pItemList[cItemIndex]->m_cName);
	}
}

void CClient::ApplyPKPenalty(short sVictimH)
{
	int iV1, iV2;

	if (g_clientList[sVictimH] == NULL) return;
	if ((m_bIsSafeAttackMode == TRUE) && (m_iPKCount == 0)) return; 

	iV1 = dice((g_clientList[sVictimH]->m_iLevel/2)+1, 50); 
	iV2 = dice((m_iLevel/2)+1, 50);

	m_iExp -= iV1; 
	m_iExp -= iV2;
	if (m_iExp < 0) m_iExp = 0;


	IncPKCount();

	g_game->_bPKLog(PKLOG_BYPK,m_handle,sVictimH,NULL) ;
	g_game->m_stCityStatus[m_side].iCrimes++;

	m_reputation -= 5;

	if(m_side != NEUTRAL)
	{
		#ifndef PKPENALTY               
			if (strcmp(g_mapList[m_cMapIndex]->m_cLocationName, sideMap[m_side]) != 0 ) return ;
		#endif
		ZeroMemory(m_cLockedMapName, sizeof(m_cLockedMapName));
		strcpy(m_cLockedMapName, sideMapJail[m_side]);
		m_iLockedMapTime = 60*3;
		g_game->RequestTeleportHandler(m_handle, 2, m_cLockedMapName, -1, -1);
	}
}

bool CClient::IsInFoeMap()
{
	switch(m_side)
	{
	case ARESDEN:
		if(strcmp(g_mapList[ m_cMapIndex ]->m_cLocationName, sideMap[ELVINE]) == 0)
		{
			return TRUE;
		}
		break;
	case ELVINE:
		if(strcmp(g_mapList[ m_cMapIndex ]->m_cLocationName, sideMap[ARESDEN]) == 0)
		{
			return TRUE;
		}
		break;
	}

	return FALSE;
}

bool CClient::IsInJail()
{ 
	return (memcmp( g_mapList[m_cMapIndex]->m_cLocationName + 3, "jail", 4) == 0) 
		? TRUE : FALSE; 
}

void CClient::ApplyElo(CClient * foe)
{
	float E; // Expected score

	float lvlFactor = 1.0f;
	if(m_iLevel > foe->m_iLevel)
		lvlFactor = 1 - logb( (float)(m_iLevel - foe->m_iLevel), 180.0);
	else if(m_iLevel < foe->m_iLevel)
		lvlFactor = logb( (float)(foe->m_iLevel - m_iLevel), 180.0);

	E = 1 / ( 1 + pow((float)10,  (float)((foe->m_elo - m_elo)/400.0))  );

	m_elo = lvlFactor * K * (1 - E);

// 	ek += 0.5 + pow((float)(( (foeElo-elo) / 1000.0) + 1), (float)2.5)
// 		* ((foeElo / 1000.0) * 1.5);

	E = 1 / ( 1 + pow((float)10,  (float)((m_elo - foe->m_elo)/400.0))  );

	foe->m_elo += lvlFactor * K * (0 - E);;

	// 	float ekA;
	// 	ekA = 0.75 * pow((float)(( (elo-foeElo) / 1000.0) + 1), (float)2.5)
	// 		* ((foeElo / 1000.0) * 1.5);
	// 	ek -= ekA;
	// 	if(ek < 0) ek = 0;
}

void CClient::DecPKCount()
{
	if (m_iPKCount > 0) {
		m_iPKCount--;
		g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_PKPENALTY, NULL, NULL, NULL, NULL);
		g_game->_bPKLog(PKLOG_REDUCECRIMINAL,(int) -1,m_handle,NULL);
		if(m_iPKCount == 0)
		{	
			SetStatusFlag(STATUS_PK, FALSE);
			g_game->SendEventToNearClient_TypeA(m_handle, OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);
		}

	}
}

void CClient::IncPKCount()
{
	m_iPKCount++;
	SetStatusFlag(STATUS_PK, TRUE);

	g_game->SendNotifyMsg(NULL, m_handle, NOTIFY_PKPENALTY, NULL, NULL, NULL, NULL);
	g_game->SendEventToNearClient_TypeA(m_handle, OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);
}

void CClient::Notify(int iFromH, WORD wMsgType, DWORD sV1, DWORD sV2, DWORD sV3, char * pString, 
	DWORD sV4, DWORD sV5, DWORD sV6, DWORD sV7, DWORD sV8, DWORD sV9, char * pString2) const
{
	g_game->SendNotifyMsg(iFromH, this->m_handle, wMsgType, sV1, sV2, sV3, pString, 
		sV4, sV5, sV6, sV7, sV8, sV9, pString2);
}

DWORD CClient::HasItem(char * name) const
{
	char cTmpName[21];

	ZeroMemory(cTmpName, sizeof(cTmpName));
	strcpy(cTmpName, name);

	for (int i = 0; i < MAXITEMS; i++)
	{
		if (m_pItemList[i] && 
			memcmp(m_pItemList[i]->m_cName, cTmpName, 20) == 0) 
		{
			return i;
		}
	}

	return ITEM_NONE;
}

DWORD CClient::HasItem(ItemID id) const
{
	for (int i = 0; i < MAXITEMS; i++)
	{
		if (m_pItemList[i] && 
			m_pItemList[i]->m_sIDnum == id) 
		{
			return i;
		}
	}

	return ITEM_NONE;
}

float CClient::GetDropFactor() const
{
	int rep = m_reputation;
	if(rep < 0)
		rep = 0;

	float factor = 1 / ((3*log10((float)rep+10) + log10((float)m_iContribution+10)) / 5);
	if(IsHeldWinner()) factor *= 0.75;
	return factor;
}
 bool CClient::IsHeldWinner() const
{
	switch(g_game->m_iLastHeldenianType)
	{
	case 1:
		return  (m_side == g_game->m_iHeldenianType1Winner);

	case 2:
		return  (m_side == g_game->m_iHeldenianType2Winner);
	}
	return FALSE;
}
 bool CClient::IsHeldLoser() const
{
	switch(g_game->m_iLastHeldenianType)
	{
	case 1:
		return  (m_side != g_game->m_iHeldenianType1Winner);

	case 2:
		return  (m_side != g_game->m_iHeldenianType2Winner);
	}
	return FALSE;
}
bool CClient::CheckNearbyFlags()
{
	if (!g_game->m_bHeldenianMode || g_game->m_iHeldenianType != 1 ||
		m_cMapIndex != g_game->m_iBtFieldMapIndex)
		return FALSE;

	COccupyFlag ** flagList = g_mapList[g_game->m_iBtFieldMapIndex]->m_pOccupyFlag;
	COccupyFlag * flag;
	for (int i = 1; i < MAXOCCUPYFLAG; i++)
	{
		flag = flagList[i];

		if (flag && flag->m_side == m_side && 
			abs(flag->m_sX - m_sX) < FLAGRANGE_X &&
			abs(flag->m_sY - m_sY) < FLAGRANGE_Y)
		{
			return TRUE;
		}
	}

	return FALSE;
}