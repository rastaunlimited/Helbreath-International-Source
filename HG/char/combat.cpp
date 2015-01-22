#include "combat.h"
#include "..\HG.h"
#include "..\map\map.h"
#include "skill.h"

extern class CGame *   g_game;
extern class CClient ** g_clientList;
extern class CMap	**	g_mapList;
extern class CNpc **	g_npcList;


extern char g_cTxt[512];

extern char _tmp_cTmpDirX[9];
extern char _tmp_cTmpDirY[9];


extern int * g_skillSSNpoint;

bool CheckResistingMagicSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio)
{
	double dTmp1, dTmp2, dTmp3;
	int    iTarGetMagicResistRatio, iDestHitRatio, iResult;
	char   cTargetDir, cProtect;								 

	switch (cTargetType) {
	case OWNERTYPE_PLAYER:
		if (g_clientList[sTargetH] == NULL) return FALSE;
		if (g_clientList[sTargetH]->IsInvincible()) return TRUE;

		cTargetDir = g_clientList[sTargetH]->m_cDir;
		//iTarGetMagicResistRatio = g_clientList[sTargetH]->m_cSkillMastery[SKILL_MAGICRES] +g_clientList[sTargetH]->m_iAddMR; 
iTarGetMagicResistRatio = g_clientList[sTargetH]->m_iAddMR; 

		if (g_clientList[sTargetH]->GetMag() > 50) 
			iTarGetMagicResistRatio += (g_clientList[sTargetH]->GetMag() - 50);

		iTarGetMagicResistRatio += g_clientList[sTargetH]->m_iAddResistMagic;
		cProtect = g_clientList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT]; 
		if ((g_clientList[sTargetH]->m_iStatus & STATUS_REDSLATE) != 0) return TRUE;
		break;

	case OWNERTYPE_NPC:
		if (g_npcList[sTargetH] == NULL) return FALSE;
		cTargetDir = g_npcList[sTargetH]->m_cDir;
		iTarGetMagicResistRatio = g_npcList[sTargetH]->m_cResistMagic;
		cProtect = g_npcList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT]; 
		break;
	}

	if (cProtect == MAGICPROTECT_AMP) return TRUE;

	if (iHitRatio < 1000 && cProtect == MAGICPROTECT_PFM) return TRUE;
	if (iHitRatio >= 10000) iHitRatio -= 10000;

	if (iTarGetMagicResistRatio < 1) iTarGetMagicResistRatio = 1;

	dTmp1 = (double)(iHitRatio);
	dTmp2 = (double)(iTarGetMagicResistRatio);

	dTmp3 = (dTmp1 / dTmp2) * 50.0f;
	iDestHitRatio = (int)(dTmp3); 

	if (iDestHitRatio < MINIMUMHITRATIO) iDestHitRatio = MINIMUMHITRATIO;
	if (iDestHitRatio > MAXIMUMHITRATIO) iDestHitRatio = MAXIMUMHITRATIO;

	if (iDestHitRatio >= 100) return FALSE;

	iResult = dice(1, 100);
	if (iResult <= iDestHitRatio) return FALSE;

	// Resisting Magic
	//if (cTargetType == OWNERTYPE_PLAYER)
		//CalculateSSN_SkillIndex(sTargetH, SKILL_MAGICRES, 1);

	return TRUE;
}


bool checkResistingPoisonSuccess(short sOwnerH, char cOwnerType)
{
	int iResist, iResult;

	switch (cOwnerType) {
	case OWNERTYPE_PLAYER:
		if (g_clientList[sOwnerH] == NULL) return FALSE;
		iResist =  g_clientList[sOwnerH]->m_iAddPR;
		//iResist = g_clientList[sOwnerH]->m_cSkillMastery[SKILL_POISONRES] + g_clientList[sOwnerH]->m_iAddPR;
		break;

	case OWNERTYPE_NPC:
		if (g_npcList[sOwnerH] == NULL) return FALSE;
		iResist = 0;
		break;
	}

	iResult = dice(1, 100);
	if (iResult >= iResist) 		return FALSE;

	//if (cOwnerType == OWNERTYPE_PLAYER)
		//CalculateSSN_SkillIndex(sOwnerH, SKILL_POISONRES, 1);

	return TRUE;
}

bool checkResistingIceSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio)
{

	int    iTargetIceResistRatio, iResult;

	switch (cTargetType) {
	case OWNERTYPE_PLAYER:
		if (g_clientList[sTargetH] == NULL) return FALSE;

		if (g_clientList[sTargetH]->IsInvincible()) return TRUE;

		if ( g_clientList[sTargetH]->m_sItemEquipmentStatus[ EQUIPPOS_BODY ] == 770 ||
			g_clientList[sTargetH]->m_sItemEquipmentStatus[ EQUIPPOS_BODY ] == 771 )
			return TRUE;

		iTargetIceResistRatio = g_clientList[sTargetH]->m_iAddAbsWater*2; 

		if (g_clientList[sTargetH]->m_dwWarmEffectTime == NULL) {
		}
		else if ((timeGetTime() - g_clientList[sTargetH]->m_dwWarmEffectTime) < 1000*30) return TRUE;
		break;

	case OWNERTYPE_NPC:
		if (g_npcList[sTargetH] == NULL) return FALSE;
		if (g_npcList[sTargetH]->m_cAttribute == ATTRIBUTE_WATER) return TRUE; 
		iTargetIceResistRatio = (g_npcList[sTargetH]->m_cResistMagic) - (g_npcList[sTargetH]->m_cResistMagic/3); 
		break;
	}

	if (iTargetIceResistRatio < 1) iTargetIceResistRatio = 1;

	iResult = dice(1, 100);
	if (iResult <= iTargetIceResistRatio) return TRUE;

	return FALSE;
}

void CalculateSSN_SkillIndex(int iClientH, short sSkillIndex, int iValue)
{
	int   iOldSSN, iSSNpoint, iWeaponIndex;

	if (g_clientList[iClientH] == NULL) return;
	if (g_clientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if ((sSkillIndex < 0) || (sSkillIndex >= MAXSKILLTYPE)) return;
	if (g_clientList[iClientH]->m_bIsKilled == TRUE) return;

	if (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] == 0) return;

	switch (sSkillIndex) {
			
	case SKILL_AGILITY:			
	case SKILL_PRAYER:			
	case SKILL_PRETENDCORPSE:
		iValue *= iValue*8;
		break;
	case SKILL_CRAFTING:case SKILL_FARMING:
	case SKILL_MANUFACTURING:
	case SKILL_ALCHEMY:
	case SKILL_MINING:
	case SKILL_FISHING:
		iValue *= iValue*2;
		break;
	}

	iOldSSN = g_clientList[iClientH]->m_iSkillSSN[sSkillIndex];
	g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] += iValue;

	iSSNpoint = g_skillSSNpoint[ g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]+1 ];

	if ( (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] < 100) &&
		(g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] > iSSNpoint) ) {

			g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]++; 
			switch (sSkillIndex) 
			{
			case SKILL_MINING:
			case SKILL_MANUFACTURING:
				if (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] > (g_clientList[iClientH]->GetStr() * 2)) {
					g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]--;
					g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = iOldSSN;
				}
				else g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = 0;
				break;

			//case SKILL_MAGICRES:
			case SKILL_PRETENDCORPSE:
				case SKILL_FISHING:
			
				if (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] > (g_clientList[iClientH]->m_iLevel * 2)) {
					g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]--;
					g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = iOldSSN;
				}
				else g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = 0;
				break;

			////case SKILL_MAGIC:
			////case SKILL_STAFF:
			//	if (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] > (g_clientList[iClientH]->GetMag() * 2)) {
			//		g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]--;
			//		g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = iOldSSN;
			//	}
			//	else g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = 0;
			//	break;

			
		//	case SKILL_DEFENSE:
			/*
				if (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] > (g_clientList[iClientH]->GetDex() * 2)) {
					g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]--;
					g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = iOldSSN;
				}
				else g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = 0;
				break;
*/
			case SKILL_FARMING:
			case SKILL_ALCHEMY:
				case SKILL_CRAFTING:	
				if (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] > (g_clientList[iClientH]->GetInt() * 2)) {
					g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]--;
					g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = iOldSSN;
				}
				else g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = 0;
				break;

			/*case SKILL_POISONRES:
				if (g_clientList[iClientH]->m_cSkillMastery[sSkillIndex] > (g_clientList[iClientH]->m_iVit * 2)) {
					g_clientList[iClientH]->m_cSkillMastery[sSkillIndex]--;
					g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = iOldSSN;
				}
				else g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = 0;
				break;*/

			default:
				g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] = 0;
				break;
			}

			if (g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] == 0) {
				if (g_clientList[iClientH]->m_sItemEquipmentStatus[ EQUIPPOS_TWOHAND ] != -1) {
					iWeaponIndex = g_clientList[iClientH]->m_sItemEquipmentStatus[ EQUIPPOS_TWOHAND ];
					if (g_clientList[iClientH]->m_pItemList[iWeaponIndex]->m_sRelatedSkill == sSkillIndex) {
						g_clientList[iClientH]->m_iHitRatio++;
					}
				}

				if (g_clientList[iClientH]->m_sItemEquipmentStatus[ EQUIPPOS_RHAND ] != -1) {
					iWeaponIndex = g_clientList[iClientH]->m_sItemEquipmentStatus[ EQUIPPOS_RHAND ];
					if (g_clientList[iClientH]->m_pItemList[iWeaponIndex]->m_sRelatedSkill == sSkillIndex) {
						g_clientList[iClientH]->m_iHitRatio++;
					}
				}
			}

			if (g_clientList[iClientH]->m_iSkillSSN[sSkillIndex] == 0) {
				g_clientList[iClientH]->CheckTotalSkillMasteryPoints(sSkillIndex);

				g_game->SendNotifyMsg(NULL, iClientH, NOTIFY_SKILL, sSkillIndex, g_clientList[iClientH]->m_cSkillMastery[sSkillIndex], NULL, NULL);
			}
	}
}


void CalculateSSN_ItemIndex(int iClientH, short sWeaponIndex, int iValue)
{
	short sSkillIndex;

	if (g_clientList[iClientH] == NULL) return;
	if (g_clientList[iClientH]->m_bIsInitComplete == FALSE) return;
	if (g_clientList[iClientH]->m_pItemList[sWeaponIndex] == NULL) return;
	if (g_clientList[iClientH]->m_bIsKilled == TRUE) return;

	sSkillIndex = g_clientList[iClientH]->m_pItemList[sWeaponIndex]->m_sRelatedSkill;

	CalculateSSN_SkillIndex(iClientH, sSkillIndex,iValue);
	
}

int calculateAttackEffect(short sTargetH, char cTargetType, short sAttackerH, char cAttackerType, int tdX, int tdY, int iAttackMode, bool bNearAttack, bool bIsDash)
{
	int    iAP_SM, iAP_L, iAttackerHitRatio, iTargetDefenseRatio, iDestHitRatio, iResult, iAP_Abs_Armor, iAP_Abs_Shield;
	char   cAttackerName[21], cAttackerDir, cAttackerSide, cTargetDir, cProtect;
	short  sWeaponIndex, sAttackerWeapon, dX, dY, sX, sY, sAtkX, sAtkY, sTgtX, sTgtY;
	DWORD  dwTime = timeGetTime();
	WORD   wWeaponType;
	double dTmp1, dTmp2, dTmp3;
	bool   bKilled = FALSE;
	bool   bNormalMissileAttack = FALSE;
	bool   bIsAttackerBerserk;
	int    iKilledDice, iDamage, iExp, iWepLifeOff, iSideCondition, iMaxSuperAttack, iWeaponSkill, iComboBonus, iTemp,iTemp2;
	int    iAttackerHP, iMoveDamage;
	char   cAttackerSA;
	int    iAttackerSAvalue, iHitPoint;
	char   cDamageMoveDir;
	int    iPartyID, iConstructionPoint, iWarContribution, tX, tY, iDst1, iDst2;
	int	iSkillLV,iCropLimit;

	iExp = 0;
	iPartyID = 0;

	ZeroMemory(cAttackerName, sizeof(cAttackerName));
	cAttackerSA      = NULL;
	iAttackerSAvalue = NULL;
	wWeaponType      = NULL;


	switch (cAttackerType) {
	case OWNERTYPE_PLAYER:

		if (g_clientList[sAttackerH] == NULL) return 0;


		if (g_mapList[ g_clientList[sAttackerH]->m_cMapIndex ]->m_bIsAttackEnabled == FALSE) return 0;


		if ( (g_clientList[sAttackerH]->m_iStatus & STATUS_INVISIBILITY) != 0 ) {
			g_clientList[sAttackerH]->SetMagicFlag(MAGICTYPE_INVISIBILITY, FALSE);

			g_game->RemoveFromDelayEventList(sAttackerH, OWNERTYPE_PLAYER, MAGICTYPE_INVISIBILITY);
			g_clientList[sAttackerH]->m_cMagicEffectStatus[ MAGICTYPE_INVISIBILITY ] = NULL;
		}

		if ((g_clientList[sAttackerH]->m_sAppr2 & 0xF000) == 0) return 0;

		iAP_SM = 0;
		iAP_L  = 0;


		wWeaponType = ((g_clientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);


		cAttackerSide = g_clientList[sAttackerH]->m_side;

		if (wWeaponType == 0) {
			iAP_SM = iAP_L    = dice(1, (g_clientList[sAttackerH]->GetStr() / 12));
			if (iAP_SM <= 0) iAP_SM = 1;
			if (iAP_L  <= 0) iAP_L  = 1;
			iAttackerHitRatio = g_clientList[sAttackerH]->m_iHitRatio;// + g_clientList[sAttackerH]->m_cSkillMastery[SKILL_HANDATTACK];

			//g_clientList[sAttackerH]->m_sUsingWeaponSkill = SKILL_HANDATTACK;

		}
		else if ((wWeaponType >= 1) && (wWeaponType < 40)) {

			iAP_SM = dice(g_clientList[sAttackerH]->m_cAttackDiceThrow_SM, g_clientList[sAttackerH]->m_cAttackDiceRange_SM);
			iAP_L  = dice(g_clientList[sAttackerH]->m_cAttackDiceThrow_L, g_clientList[sAttackerH]->m_cAttackDiceRange_L);


			iAP_SM += g_clientList[sAttackerH]->m_cAttackBonus_SM;
			iAP_L  += g_clientList[sAttackerH]->m_cAttackBonus_L;

			iAttackerHitRatio = g_clientList[sAttackerH]->m_iHitRatio;


			dTmp1 = (double)iAP_SM;
			if (g_clientList[sAttackerH]->GetStr() <= 0)
				dTmp2 = 1.0f;
			else dTmp2 = (double)g_clientList[sAttackerH]->GetStr();

			dTmp2 = dTmp2 / 5.0f;
			dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
			iAP_SM = (int)(dTmp3 +0.5f);

			dTmp1 = (double)iAP_L;
			if (g_clientList[sAttackerH]->GetStr() <= 0)
				dTmp2 = 1.0f;
			else dTmp2 = (double)g_clientList[sAttackerH]->GetStr();

			dTmp2 = dTmp2 / 5.0f;
			dTmp3 = dTmp1 + (dTmp1 * (dTmp2 / 100.0f));
			iAP_L = (int)(dTmp3 +0.5f);
			//
		}
		else if (wWeaponType >= 40) {
			iAP_SM = dice(g_clientList[sAttackerH]->m_cAttackDiceThrow_SM, g_clientList[sAttackerH]->m_cAttackDiceRange_SM);
			iAP_L  = dice(g_clientList[sAttackerH]->m_cAttackDiceThrow_L, g_clientList[sAttackerH]->m_cAttackDiceRange_L);


			iAP_SM += g_clientList[sAttackerH]->m_cAttackBonus_SM;
			iAP_L  += g_clientList[sAttackerH]->m_cAttackBonus_L;

			iAttackerHitRatio = g_clientList[sAttackerH]->m_iHitRatio;
			bNormalMissileAttack = TRUE;


			iAP_SM += dice(1, (g_clientList[sAttackerH]->GetStr() / 20));
			iAP_L  += dice(1, (g_clientList[sAttackerH]->GetStr() / 20));
			//
		}


		if (g_clientList[sAttackerH]->m_iCustomItemValue_Attack != 0) {

			if ((g_clientList[sAttackerH]->m_iMinAP_SM != 0) && (iAP_SM < g_clientList[sAttackerH]->m_iMinAP_SM)) {
				iAP_SM = g_clientList[sAttackerH]->m_iMinAP_SM;
			}
			if ((g_clientList[sAttackerH]->m_iMinAP_L != 0) && (iAP_L < g_clientList[sAttackerH]->m_iMinAP_L)) {
				iAP_L = g_clientList[sAttackerH]->m_iMinAP_L;
			}

			if ((g_clientList[sAttackerH]->m_iMaxAP_SM != 0) && (iAP_SM > g_clientList[sAttackerH]->m_iMaxAP_SM)) {
				iAP_SM = g_clientList[sAttackerH]->m_iMaxAP_SM;
			}
			if ((g_clientList[sAttackerH]->m_iMaxAP_L != 0) && (iAP_L > g_clientList[sAttackerH]->m_iMaxAP_L)) {
				iAP_L = g_clientList[sAttackerH]->m_iMaxAP_L;
			}
		}

		cAttackerDir = g_clientList[sAttackerH]->m_cDir;
		strcpy(cAttackerName, g_clientList[sAttackerH]->m_cCharName);

		bIsAttackerBerserk = g_clientList[sAttackerH]->IsBerserked();

		if ((g_clientList[sAttackerH]->m_iSuperAttackLeft > 0) && (iAttackMode >= 20)) {

			dTmp1 = (double)iAP_SM;
			dTmp2 = (double)g_clientList[sAttackerH]->m_iLevel;
			dTmp3 = dTmp2 / 100.0f;
			dTmp2 = dTmp1 * dTmp3;
			iTemp = (int)(dTmp2 +0.5f);
			iAP_SM += iTemp;

			dTmp1 = (double)iAP_L;
			dTmp2 = (double)g_clientList[sAttackerH]->m_iLevel;
			dTmp3 = dTmp2 / 100.0f;
			dTmp2 = dTmp1 * dTmp3;
			iTemp = (int)(dTmp2 +0.5f);
			iAP_L += iTemp;

			/*switch (g_clientList[sAttackerH]->m_sUsingWeaponSkill) 
			{
			case SKILL_ARCHERY:
				iAP_SM += (iAP_SM/10); iAP_L += (iAP_L/10);
				iAttackerHitRatio  += 30;
				break;
			case SKILL_SHORTSWORD:
				iAP_SM *= 2; iAP_L *= 2;
				break;
			case SKILL_LONGSWORD:
				iAP_SM += (iAP_SM/10); iAP_L += (iAP_L/10);
				iAttackerHitRatio += 30;
				break;
			case SKILL_AXE:
				iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5);
				break;
			case SKILL_HAMMER:
				iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5);
				iAttackerHitRatio += 20;
				break;   
			case SKILL_STAFF:  
				iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5);
				iAttackerHitRatio +=  50;
				break;
			}*/
			iAP_SM += (iAP_SM/10); iAP_L += (iAP_L/10);
				iAttackerHitRatio += 30;


			iAttackerHitRatio += 100;
			iAttackerHitRatio += g_clientList[sAttackerH]->m_iCustomItemValue_Attack;
		}


		if (bIsDash == TRUE) {

			iAttackerHitRatio += 30;

		/*	switch (g_clientList[sAttackerH]->m_sUsingWeaponSkill) {
			case SKILL_LONGSWORD:  
				iAP_SM += (iAP_SM/10); iAP_L += (iAP_L/10); 
				break;
			case SKILL_AXE: 
				iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5);
				break;
			case SKILL_HAMMER:
				iAP_SM += (iAP_SM/5); iAP_L += (iAP_L/5);
				break;
			}*/
		}

		iAttackerHP = g_clientList[sAttackerH]->m_iHP;

		iAttackerHitRatio += g_clientList[sAttackerH]->m_iAddAR;

		sAtkX = g_clientList[sAttackerH]->m_sX;
		sAtkY = g_clientList[sAttackerH]->m_sY;

		iPartyID = g_clientList[sAttackerH]->m_iPartyID;

		break;

	case OWNERTYPE_NPC:
		if (g_npcList[sAttackerH] == NULL) return 0;

		if (g_mapList[ g_npcList[sAttackerH]->m_cMapIndex ]->m_bIsAttackEnabled == FALSE) return 0;

		if ( (g_npcList[sAttackerH]->m_iStatus & STATUS_INVISIBILITY) != 0 ) {
			g_npcList[sAttackerH]->SetMagicFlag(MAGICTYPE_INVISIBILITY, FALSE);

			g_game->RemoveFromDelayEventList(sAttackerH, OWNERTYPE_NPC, MAGICTYPE_INVISIBILITY);
			g_npcList[ sAttackerH ]->m_cMagicEffectStatus[ MAGICTYPE_INVISIBILITY ] = NULL;
		}


		cAttackerSide = g_npcList[sAttackerH]->m_side;

		iAP_SM = 0;
		iAP_L  = 0;

		// Crusade
		if (g_npcList[sAttackerH]->m_cAttackDiceThrow != 0) 
			iAP_L = iAP_SM = dice(g_npcList[sAttackerH]->m_cAttackDiceThrow, g_npcList[sAttackerH]->m_cAttackDiceRange);

		iAttackerHitRatio = g_npcList[sAttackerH]->m_iHitRatio;

		cAttackerDir = g_npcList[sAttackerH]->m_cDir;
		memcpy(cAttackerName, g_npcList[sAttackerH]->m_cNpcName, 20);

		if (g_npcList[sAttackerH]->IsBerserked())
			bIsAttackerBerserk = TRUE;
		else bIsAttackerBerserk = FALSE;


		iAttackerHP = g_npcList[sAttackerH]->m_iHP;


		cAttackerSA = g_npcList[sAttackerH]->m_cSpecialAbility;

		sAtkX = g_npcList[sAttackerH]->m_sX;
		sAtkY = g_npcList[sAttackerH]->m_sY;
		break;
	}

	switch (cTargetType) {
	case OWNERTYPE_PLAYER:

		if (g_clientList[sTargetH] == NULL) return 0;

		if (g_clientList[sTargetH]->m_bIsKilled == TRUE) return 0;

#ifdef SAMESIDETOWNPROTECT

		if ((g_clientList[sTargetH]->m_iPKCount == 0) && (cAttackerType == OWNERTYPE_PLAYER) && (g_clientList[sTargetH]->m_side == cAttackerSide) && (g_clientList[sTargetH]->m_iIsOnTown == NONPK)) return 0;
#endif 
#ifdef BEGINNERTOWNPROTECT
		if ((cAttackerType == OWNERTYPE_PLAYER) && (g_clientList[sTargetH]->m_bIsNeutral == TRUE)
			&& (g_clientList[sTargetH]->m_iPKCount == 0) && (g_clientList[sTargetH]->m_iIsOnTown == NONPK)) return 0;
#endif

		if ((g_clientList[sTargetH]->m_sX != tdX) || (g_clientList[sTargetH]->m_sY != tdY)) return 0;

		if (g_clientList[sTargetH]->IsInvincible()) return 0;

		if ((cAttackerType == OWNERTYPE_PLAYER) && (g_clientList[sAttackerH]->m_bIsNeutral == TRUE) && (g_clientList[sTargetH]->m_iPKCount == 0)) return 0;

		if ((g_clientList[sTargetH]->m_iPartyID != NULL) && (iPartyID == g_clientList[sTargetH]->m_iPartyID)) return 0;

		if ((g_clientList[sTargetH]->m_iStatus & STATUS_REDSLATE) != 0) return 0;

		cTargetDir = g_clientList[sTargetH]->m_cDir;
		iTargetDefenseRatio = g_clientList[sTargetH]->m_iDefenseRatio;

		if ((cAttackerType == OWNERTYPE_PLAYER) && (g_clientList[sAttackerH]->m_bIsSafeAttackMode == TRUE)) {
			iSideCondition = g_clientList[sAttackerH]->GetPlayerRelationship(sTargetH);
			if ((iSideCondition == 7) || (iSideCondition == 2) || (iSideCondition == 6)) {

				iAP_SM = iAP_SM / 2;
				iAP_L  = iAP_L / 2;
			}
			else {

				if (g_mapList[g_clientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) {
					if (g_clientList[sAttackerH]->m_iGuildGUID == g_clientList[sTargetH]->m_iGuildGUID) return 0;
					else {

						iAP_SM = iAP_SM / 2;
						iAP_L  = iAP_L / 2;
					}
				}
				else return 0;
			}
		}

		iTargetDefenseRatio += g_clientList[sTargetH]->m_iAddDR;

		sTgtX = g_clientList[sTargetH]->m_sX;
		sTgtY = g_clientList[sTargetH]->m_sY;
		break;

	case OWNERTYPE_NPC:

		if (g_npcList[sTargetH] == NULL) return 0;

		if (g_npcList[sTargetH]->m_iHP <= 0) return 0;

		if ((g_npcList[sTargetH]->m_sX != tdX) || (g_npcList[sTargetH]->m_sY != tdY)) return 0;

		cTargetDir = g_npcList[sTargetH]->m_cDir;
		iTargetDefenseRatio = g_npcList[sTargetH]->m_iDefenseRatio;


		if (cAttackerType == OWNERTYPE_PLAYER) {
			switch (g_npcList[sTargetH]->m_sType) 
			{
			case NPC_ESG:
			case NPC_GMG:
				if ((g_clientList[sAttackerH]->m_side == NEUTRAL) || (g_npcList[sTargetH]->m_side == g_clientList[sAttackerH]->m_side)) return 0;
				break;
			}

			if ((wWeaponType == 25) && (g_npcList[sTargetH]->m_cActionLimit == 5) && (g_npcList[sTargetH]->m_iBuildCount > 0)) {

				if (g_clientList[sAttackerH]->m_iCrusadeDuty != 2 && !g_game->m_astoria.get() && (g_clientList[sAttackerH]->m_iAdminUserLevel == 0)) break;
				
				switch (g_npcList[sTargetH]->m_sType) {
				case NPC_AGT:
				case NPC_CGT:
				case NPC_MS:
				case NPC_DT:
					if(g_clientList[sAttackerH]->IsGM()) g_npcList[sTargetH]->m_iBuildCount = 1;
					switch (g_npcList[sTargetH]->m_iBuildCount) {
					case 1: 		
						g_npcList[sTargetH]->m_sAppr2 = 0;
						g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);

						if(g_game->m_bIsCrusadeMode)
						{
						switch (g_npcList[sTargetH]->m_sType) 
						{
						case NPC_AGT: iConstructionPoint = 700; iWarContribution = 700; break;
						case NPC_CGT: iConstructionPoint = 700; iWarContribution = 700; break;
						case NPC_MS: iConstructionPoint = 500; iWarContribution = 500; break;		
						case NPC_DT: iConstructionPoint = 500; iWarContribution = 500; break;
						}

						g_clientList[sAttackerH]->m_iWarContribution   += iWarContribution;
						if (g_clientList[sAttackerH]->m_iWarContribution > MAXWARCONTRIBUTION)
							g_clientList[sAttackerH]->m_iWarContribution = MAXWARCONTRIBUTION;

						g_game->SendNotifyMsg(NULL, sAttackerH, NOTIFY_CONSTRUCTIONPOINT, g_clientList[sAttackerH]->m_iConstructionPoint, g_clientList[sAttackerH]->m_iWarContribution, NULL, NULL);
						}
						break;
					case 5: 		
						g_npcList[sTargetH]->m_sAppr2 = 1;
						g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);
						break;
					case 10: 
						g_npcList[sTargetH]->m_sAppr2 = 2;
						g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);
						break;
					}
					break;
				}

				g_npcList[sTargetH]->m_iBuildCount--;
				if (g_npcList[sTargetH]->m_iBuildCount <= 0) {
					g_npcList[sTargetH]->m_iBuildCount = 0;
				}
				return 0;
			}


			if ((wWeaponType == 27) && (g_npcList[sTargetH]->m_iNpcCrops != 0) && (g_npcList[sTargetH]->m_cActionLimit == 5) && (g_npcList[sTargetH]->m_iBuildCount > 0)) {

				iSkillLV = g_clientList[sAttackerH]->m_cSkillMastery[SKILL_FARMING];
				iCropLimit = g_npcList[sTargetH]->m_iCropsSkillLV;

				if(20 > iSkillLV) return 0;  

				if(g_clientList[sAttackerH]->m_iLevel <  20 ) return 0 ; 


				switch (g_npcList[sTargetH]->m_sType) {
				case NPC_CROPS:
					switch (g_npcList[sTargetH]->m_iBuildCount) {
					case 1: 
						g_npcList[sTargetH]->m_sAppr2 = g_npcList[sTargetH]->m_iNpcCrops << 8 | 3;
						//						g_npcList[sTargetH]->m_sAppr2 = (char)0;

						if(iSkillLV <= iCropLimit + 10)
							CalculateSSN_SkillIndex(sAttackerH, SKILL_FARMING, 1);

						g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);


						if(probabilityTable(iSkillLV,iCropLimit,2) > 0)
						{
							g_game->bCropsItemDrop(sAttackerH,sTargetH,TRUE);
						}
						g_game->DeleteNpc(sTargetH);

						break;
					case 8: 		
						g_npcList[sTargetH]->m_sAppr2 = g_npcList[sTargetH]->m_iNpcCrops << 8 | 3;
						//						g_npcList[sTargetH]->m_sAppr2 = (char)3;

						if(iSkillLV <= iCropLimit + 10)
							CalculateSSN_SkillIndex(sAttackerH, SKILL_FARMING, 1);

						g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);


						if(probabilityTable(iSkillLV,iCropLimit,2) > 0)
						{
							if(iSkillLV <= iCropLimit + 10)
								CalculateSSN_SkillIndex(sAttackerH, SKILL_FARMING, 1);
							g_game->bCropsItemDrop(sAttackerH,sTargetH);
						}
						break;

					case 18: 
						g_npcList[sTargetH]->m_sAppr2 = g_npcList[sTargetH]->m_iNpcCrops << 8 | 2;
						//						g_npcList[sTargetH]->m_sAppr2 = (char)2;

						if(iSkillLV <= iCropLimit + 10)
							CalculateSSN_SkillIndex(sAttackerH, SKILL_FARMING, 1);

						g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTNULLACTION, NULL, NULL, NULL);


						if(probabilityTable(iSkillLV,iCropLimit,2) > 0)
						{
							if(iSkillLV <= iCropLimit + 10)
								CalculateSSN_SkillIndex(sAttackerH, SKILL_FARMING, 1);
							g_game->bCropsItemDrop(sAttackerH,sTargetH);
						}
						break;
					}
					break;
				}

				if(g_npcList[sTargetH] == NULL)
				{
					return 0;
				}

				if(probabilityTable(iSkillLV,iCropLimit,1) > 0 
					|| g_npcList[sTargetH]->m_iBuildCount == 1
					|| g_npcList[sTargetH]->m_iBuildCount == 8
					|| g_npcList[sTargetH]->m_iBuildCount == 18) {

						iTemp = g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_RHAND];

						if ((iTemp != -1) || (g_clientList[sAttackerH]->m_pItemList[iTemp] != NULL)) {

							if (g_clientList[sAttackerH]->m_pItemList[iTemp]->m_wCurLifeSpan > 0)
								g_clientList[sAttackerH]->m_pItemList[iTemp]->m_wCurLifeSpan--;

							if (g_clientList[sAttackerH]->m_pItemList[iTemp]->m_wCurLifeSpan <= 0) {

								g_game->SendNotifyMsg(NULL, sAttackerH, NOTIFY_ITEMLIFESPANEND, g_clientList[sAttackerH]->m_pItemList[iTemp]->m_cEquipPos, iTemp, NULL, NULL);

								g_game->ReleaseItemHandler(sAttackerH, iTemp, TRUE);  
							}
						}


						g_npcList[sTargetH]->m_iBuildCount--;
				}

				if (g_npcList[sTargetH]->m_iBuildCount <= 0) {
					g_npcList[sTargetH]->m_iBuildCount = 0;
				}

				return 0;
			}
			if (g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] != -1 &&
				g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] ] != NULL &&
				g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] ]->m_sIDnum == ITEM_DEMONSLAYER &&
				g_npcList[sTargetH]->m_sType == NPC_DEMON) {
				iAP_L += 5;
			}
		}

		sTgtX = g_npcList[sTargetH]->m_sX;
		sTgtY = g_npcList[sTargetH]->m_sY;
		break;
	}


	if ( (cAttackerType == OWNERTYPE_PLAYER) && (cTargetType == OWNERTYPE_PLAYER) ) {

		sX = g_clientList[sAttackerH]->m_sX;
		sY = g_clientList[sAttackerH]->m_sY;

		dX = g_clientList[sTargetH]->m_sX;
		dY = g_clientList[sTargetH]->m_sY;

		if (g_mapList[g_clientList[sTargetH]->m_cMapIndex]->iGetAttribute(sX, sY, 0x00000006) != 0) return 0;
		if (g_mapList[g_clientList[sTargetH]->m_cMapIndex]->iGetAttribute(dX, dY, 0x00000006) != 0) return 0;
	}


	if (cAttackerType == OWNERTYPE_PLAYER) {
		if (g_clientList[sAttackerH]->GetDex() > 50) {
			iAttackerHitRatio += (g_clientList[sAttackerH]->GetDex() - 50); 
		}
	}

	if (wWeaponType >= 40) {
		switch (g_mapList[g_clientList[sAttackerH]->m_cMapIndex]->m_cWhetherStatus) {
		case 0:	break;
		case 1:	iAttackerHitRatio = iAttackerHitRatio - (iAttackerHitRatio / 20); break;
		case 2:	iAttackerHitRatio = iAttackerHitRatio - (iAttackerHitRatio / 10); break;
		case 3:	iAttackerHitRatio = iAttackerHitRatio - (iAttackerHitRatio / 4);  break;
		}
	}
	if (iAttackerHitRatio < 0)   iAttackerHitRatio = 0;    

	switch (cTargetType) 
	{
	case OWNERTYPE_PLAYER:
		cProtect = g_clientList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT];
		break;
	case OWNERTYPE_NPC:
		cProtect = g_npcList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT]; 
		break;
	}



	if (cAttackerType == OWNERTYPE_PLAYER) {
		// BUG POINT! Item == NULL
		if (g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] != -1) {
			//#ERROR POINT!
			if (g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] ] == NULL) {

				g_clientList[sAttackerH]->m_bIsItemEquipped[g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND]] = FALSE;
				g_game->DeleteClient(sAttackerH, TRUE, TRUE);
				return 0;
			}

			if (g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] ]->m_sItemEffectType == ITEMEFFECTTYPE_ATTACK_ARROW) {
				if (g_clientList[sAttackerH]->m_cArrowIndex == -1) {
					return 0;
				}
				else {
					if (g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_cArrowIndex ] == NULL) 
						return 0;

					g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_cArrowIndex ]->m_dwCount--;
					if (g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_cArrowIndex ]->m_dwCount <= 0) {

						g_game->ItemDepleteHandler(sAttackerH, g_clientList[sAttackerH]->m_cArrowIndex, FALSE);

						g_clientList[sAttackerH]->m_cArrowIndex = g_game->_iGetArrowItemIndex(sAttackerH);
					}
					else {
						g_game->SendNotifyMsg(NULL, sAttackerH, NOTIFY_SETITEMCOUNT, g_clientList[sAttackerH]->m_cArrowIndex, g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_cArrowIndex ]->m_dwCount, (char)FALSE, NULL);
						g_game->iCalcTotalWeight(sAttackerH);
					}
				}
				if (cProtect == MAGICPROTECT_PFA) return 0;
			}
			else {
				switch (cProtect) 
				{
				case MAGICPROTECT_DS:
					iTargetDefenseRatio += 40;
					break;
				case MAGICPROTECT_GDS:
					iTargetDefenseRatio += 100;
					break;
				}
				if (iTargetDefenseRatio < 0) iTargetDefenseRatio = 1;
			}
		}
	}
	else {
		switch (cProtect) {
		case MAGICPROTECT_PFA: 
			switch (g_npcList[sAttackerH]->m_sType) 
			{
			case NPC_DARK_ELF: 
				if ((abs(sTgtX - g_npcList[sAttackerH]->m_sX) >= 1) || (abs(sTgtY - g_npcList[sAttackerH]->m_sY) >= 1)) return 0; 
			}
			break;
		case MAGICPROTECT_DS: iTargetDefenseRatio += 40;  break;
		case MAGICPROTECT_GDS: iTargetDefenseRatio += 100; break;
		}
		if (iTargetDefenseRatio < 0) iTargetDefenseRatio = 1;
	}

	if (cAttackerDir == cTargetDir) iTargetDefenseRatio = iTargetDefenseRatio / 2;

	if (iTargetDefenseRatio < 1)   iTargetDefenseRatio = 1;

	dTmp1 = (double)(iAttackerHitRatio);
	dTmp2 = (double)(iTargetDefenseRatio);

	dTmp3 = (dTmp1 / dTmp2) * HITRATIOFACTOR;
	iDestHitRatio = (int)(dTmp3); 

	if (iDestHitRatio < MINIMUMHITRATIO) iDestHitRatio = MINIMUMHITRATIO;

	if (iDestHitRatio > MAXIMUMHITRATIO) iDestHitRatio = MAXIMUMHITRATIO;

	if ((bIsAttackerBerserk == TRUE) && (iAttackMode < 20)) {
		iAP_SM = iAP_SM * 2;
		iAP_L  = iAP_L  * 2;
	}

	if (cAttackerType == OWNERTYPE_PLAYER) {
		iAP_SM += g_clientList[sAttackerH]->m_iAddPhysicalDamage;
		iAP_L  += g_clientList[sAttackerH]->m_iAddPhysicalDamage;
	}

	if (bNearAttack == TRUE) {
		iAP_SM = iAP_SM / 2;
		iAP_L  = iAP_L / 2;
	}

	if (cTargetType == OWNERTYPE_PLAYER) {
		iAP_SM -= (dice(1, g_clientList[sTargetH]->m_iVit/10) - 1);
		iAP_L  -= (dice(1, g_clientList[sTargetH]->m_iVit/10) - 1);
	}

	
	if (cAttackerType == OWNERTYPE_PLAYER) {
		if (g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] != -1 &&
			g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] ] != NULL){
				if((g_game->m_cDayOrNight == 2 && g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] ]->m_sIDnum == ITEM_DARKEXECUTOR) ||
					(g_game->m_cDayOrNight == 1 && g_clientList[sAttackerH]->m_pItemList[ g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] ]->m_sIDnum == ITEM_LIGHTINGBLADE)){
						iAP_SM += 10;
						iAP_L  += 10;
				}
		}
	}

	if (cAttackerType == OWNERTYPE_PLAYER) {
		if (iAP_SM <= 1) iAP_SM = 1;
		if (iAP_L  <= 1) iAP_L  = 1;
	}
	else {
		if (iAP_SM <= 0) iAP_SM = 0;
		if (iAP_L  <= 0) iAP_L  = 0;
	}

	iResult = dice(1, 100);

	if (iResult <= iDestHitRatio) {
		if (cAttackerType == OWNERTYPE_PLAYER) {

			if ( ((g_clientList[sAttackerH]->m_iHungerStatus <= 10) || (g_clientList[sAttackerH]->m_iSP <= 0)) && 
				(dice(1,10) == 5) ) return FALSE;

			g_clientList[sAttackerH]->m_iComboAttackCount++;
			if (g_clientList[sAttackerH]->m_iComboAttackCount < 0) g_clientList[sAttackerH]->m_iComboAttackCount = 0;
			if (g_clientList[sAttackerH]->m_iComboAttackCount > 4) g_clientList[sAttackerH]->m_iComboAttackCount = 1;

			iWeaponSkill = g_game->_iGetWeaponSkillType(sAttackerH);
			iComboBonus = g_game->iGetComboAttackBonus(iWeaponSkill, g_clientList[sAttackerH]->m_iComboAttackCount);


			if ((g_clientList[sAttackerH]->m_iComboAttackCount > 1) && (g_clientList[sAttackerH]->m_iAddCD != NULL))
				iComboBonus += g_clientList[sAttackerH]->m_iAddCD;

			iAP_SM += iComboBonus;
			iAP_L  += iComboBonus;


			switch (g_clientList[sAttackerH]->m_iSpecialWeaponEffectType) 
			{		
			case ITEMSTAT_CRITICAL: 				
				if ((g_clientList[sAttackerH]->m_iSuperAttackLeft > 0) && (iAttackMode >= 20)) {
					iAP_SM += g_clientList[sAttackerH]->m_iSpecialWeaponEffectValue;
					iAP_L  += g_clientList[sAttackerH]->m_iSpecialWeaponEffectValue;
				}
				break;

			case ITEMSTAT_POISONING: 
				cAttackerSA = 61; 
				iAttackerSAvalue = g_clientList[sAttackerH]->m_iSpecialWeaponEffectValue*5; 
				break;

			case ITEMSTAT_RIGHTEOUS: 
				cAttackerSA = 62;
				break;
			}

			if (g_mapList[g_clientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE) 
			{
				iAP_SM += iAP_SM/3;
				iAP_L  += iAP_L/3;
			}

			if (g_mapList[g_clientList[sAttackerH]->m_cMapIndex]->m_bIsApocalypseMap) 
				{
				iAP_SM *= 1.2;
				iAP_L *= 1.2;
			}

			if(g_clientList[sAttackerH]->CheckNearbyFlags())
			{
				iAP_SM *= 1.3;
				iAP_L *= 1.3;
			}

			if ((cTargetType == OWNERTYPE_PLAYER) && (g_game->m_bIsCrusadeMode == TRUE) && (g_clientList[sAttackerH]->m_iCrusadeDuty == 1)) 
			{

				if (g_clientList[sAttackerH]->m_iLevel <= 80) 
				{
					iAP_SM += iAP_SM ;
					iAP_L += iAP_L ;
				}

				else if (g_clientList[sAttackerH]->m_iLevel <= 100)
				{
					iAP_SM += (iAP_SM* 7)/10 ;
					iAP_L += (iAP_L* 7)/10 ;
				} else 
				{
					iAP_SM += iAP_SM/3; ;
					iAP_L += iAP_L/3 ;
				}
			}
		}

		switch (cTargetType) {
		case OWNERTYPE_PLAYER:
			g_game->ClearSkillUsingStatus(sTargetH);

			if ((dwTime - g_clientList[sTargetH]->m_dwTime) > RAGPROTECTIONTIME) {

				return 0;
			}
			else {

				switch (cAttackerSA) {
				case 62: 
					if (g_clientList[sTargetH]->m_reputation < 0) {

						iTemp = abs(g_clientList[sTargetH]->m_reputation) / 10;
						if (iTemp > 10) iTemp = 10;
						iAP_SM += iTemp;
					}
					break;
				}


				iAP_Abs_Armor  = 0;
				iAP_Abs_Shield = 0;

				iTemp = dice(1,10000);
				if ((iTemp >= 1) && (iTemp < 5000))           iHitPoint = 1; // BODY
				else if ((iTemp >= 5000) && (iTemp < 7500))   iHitPoint = 2; // PANTS + LEGGINGS
				else if ((iTemp >= 7500) && (iTemp < 9000))   iHitPoint = 3; // ARMS
				else if ((iTemp >= 9000) && (iTemp <= 10000)) iHitPoint = 4; // HEAD

				switch (iHitPoint) {
				case 1:
					if (g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_BODY] > 0) {

						if (g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_BODY] >= 80)
							dTmp1 = 80.0f;
						else dTmp1 = (double)g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_BODY];
						dTmp2 = (double)iAP_SM;
						dTmp3 = (dTmp1 / 100.0f) * dTmp2;

						iAP_Abs_Armor = (int)dTmp3;
					}
					break;

				case 2:
					if ((g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_PANTS] +
						g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_LEGGINGS]) > 0) {

							if ((g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_PANTS] +
								g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_LEGGINGS]) >= 80)
								dTmp1 = 80.0f;
							else dTmp1 = (double)(g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_PANTS] + g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_LEGGINGS]);
							dTmp2 = (double)iAP_SM;
							dTmp3 = (dTmp1 / 100.0f) * dTmp2;

							iAP_Abs_Armor = (int)dTmp3;
					}
					break;

				case 3: 
					if (g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_ARMS] > 0) {

						if (g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_ARMS] >= 80)
							dTmp1 = 80.0f;
						else dTmp1 = (double)g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_ARMS];
						dTmp2 = (double)iAP_SM;
						dTmp3 = (dTmp1 / 100.0f) * dTmp2;

						iAP_Abs_Armor = (int)dTmp3;
					}
					break;

				case 4:
					if (g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_HEAD] > 0) {

						if (g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_HEAD] >= 80)
							dTmp1 = 80.0f;
						else dTmp1 = (double)g_clientList[sTargetH]->m_iDamageAbsorption_Armor[EQUIPPOS_HEAD];
						dTmp2 = (double)iAP_SM;
						dTmp3 = (dTmp1 / 100.0f) * dTmp2;

						iAP_Abs_Armor = (int)dTmp3;
					}
					break;
				}

				if (g_clientList[sTargetH]->m_iDamageAbsorption_Shield > 0) {
				/*	if (dice(1,100) <= (g_clientList[sTargetH]->m_cSkillMastery[SKILL_SHIELD])) {

						CalculateSSN_SkillIndex(sTargetH, SKILL_SHIELD, 1);

						if (g_clientList[sTargetH]->m_iDamageAbsorption_Shield >= 80) 
							dTmp1 = 80.0f;
						else dTmp1 = (double)g_clientList[sTargetH]->m_iDamageAbsorption_Shield;
						dTmp2 = (double)iAP_SM - iAP_Abs_Armor;
						dTmp3 = (dTmp1 / 100.0f) * dTmp2;

						iAP_Abs_Shield = (int)dTmp3;


						iTemp = g_clientList[sTargetH]->m_sItemEquipmentStatus[EQUIPPOS_LHAND];
						if ((iTemp != -1) && (g_clientList[sTargetH]->m_pItemList[iTemp] != NULL)) {


							if (!g_clientList[sTargetH]->IsNeutral() && (g_clientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan > 0))
								g_clientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan--;

							if (g_clientList[sTargetH]->m_pItemList[iTemp]->m_wCurLifeSpan == 0) {

								g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_ITEMLIFESPANEND, g_clientList[sTargetH]->m_pItemList[iTemp]->m_cEquipPos, iTemp, NULL, NULL);

								g_game->ReleaseItemHandler(sTargetH, iTemp, TRUE);  
							}
						}
					}*/
				}

				iAP_SM = iAP_SM - (iAP_Abs_Armor + iAP_Abs_Shield);
				if (iAP_SM <= 0) iAP_SM = 1;


				if ((cAttackerType == OWNERTYPE_PLAYER) && (g_clientList[sAttackerH] != NULL) && (g_clientList[sAttackerH]->m_bIsSpecialAbilityEnabled == TRUE)) {
					switch (g_clientList[sAttackerH]->m_iSpecialAbilityType) {
					case 0: break;
					case 1: 
						iTemp = (g_clientList[sTargetH]->m_iHP / 2);
						if (iTemp > iAP_SM) iAP_SM = iTemp;
						if (iAP_SM <= 0) iAP_SM = 1;
						break;

					case 2: 
						if (g_clientList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_ICE ] == 0) {
							g_clientList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_ICE ] = 1;
							g_clientList[sTargetH]->SetStatusFlag(STATUS_FROZEN, TRUE);
							g_game->RegisterDelayEvent(DELAYEVENTTYPE_MAGICRELEASE, MAGICTYPE_ICE, dwTime + (30*1000), 
								sTargetH, OWNERTYPE_PLAYER, NULL, NULL, NULL, 1, NULL, NULL);

							g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_MAGICEFFECTON, MAGICTYPE_ICE, 1, NULL, NULL);
						}
						break;

					case 3: 
						if (g_clientList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] == 0) {
							g_clientList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] = 2;

							g_game->RegisterDelayEvent(DELAYEVENTTYPE_MAGICRELEASE, MAGICTYPE_HOLDOBJECT, dwTime + (10*1000), 
								sTargetH, OWNERTYPE_PLAYER, NULL, NULL, NULL, 10, NULL, NULL);

							g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_MAGICEFFECTON, MAGICTYPE_HOLDOBJECT, 10, NULL, NULL);
						}
						break;

					case 4: 			
						iAP_SM = (g_clientList[sTargetH]->m_iHP);
						break;

					case 5: 			
						g_clientList[sAttackerH]->m_iHP += iAP_SM;
						if (g_clientList[sAttackerH]->GetMaxHP() < g_clientList[sAttackerH]->m_iHP) 
							g_clientList[sAttackerH]->m_iHP = g_clientList[sAttackerH]->GetMaxHP();
						g_game->SendNotifyMsg(NULL, sAttackerH, NOTIFY_HP, NULL, NULL, NULL, NULL);
						break;
					}
				}


				if ((cAttackerType == OWNERTYPE_PLAYER) && (g_clientList[sAttackerH] != NULL) && (g_clientList[sTargetH]->m_bIsSpecialAbilityEnabled == TRUE)) {
					switch (g_clientList[sTargetH]->m_iSpecialAbilityType) {
					case 50: 
						if (g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] != -1)
							sWeaponIndex = g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND];
						else sWeaponIndex = g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_RHAND];
						if (sWeaponIndex != -1)	g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan = 0;
						break;

					case 51: 			
						if (iHitPoint == g_clientList[sTargetH]->m_iSpecialAbilityEquipPos)
							iAP_SM = 0;
						break;

					case 52: 			
						iAP_SM = 0;
						break;
					}
				}

				if ((g_clientList[sTargetH]->m_bIsLuckyEffect == TRUE) && 
					(dice(1,10) < 5) && (g_clientList[sTargetH]->m_iHP <= iAP_SM)) {
						iAP_SM = 1;
				}

				switch (iHitPoint) {
				case 1:
					iTemp = g_clientList[sTargetH]->m_sItemEquipmentStatus[EQUIPPOS_BODY];
					if(iTemp == -1) 
						iTemp = g_clientList[sTargetH]->m_sItemEquipmentStatus[EQUIPPOS_FULLBODY];

					EnduStrippingDamage(sTargetH, sAttackerH, cAttackerType, iTemp, 2000);
					break;

				case 2:
					iTemp = g_clientList[sTargetH]->m_sItemEquipmentStatus[EQUIPPOS_PANTS];
					EnduStrippingDamage(sTargetH, sAttackerH, cAttackerType, iTemp, 2000);

					iTemp = g_clientList[sTargetH]->m_sItemEquipmentStatus[EQUIPPOS_LEGGINGS];
					EnduStrippingDamage(sTargetH, sAttackerH, cAttackerType, iTemp, 2000);
					break;

				case 3:
					iTemp = g_clientList[sTargetH]->m_sItemEquipmentStatus[EQUIPPOS_ARMS];
					EnduStrippingDamage(sTargetH, sAttackerH, cAttackerType, iTemp, 2000);
					break;

				case 4:
					iTemp = g_clientList[sTargetH]->m_sItemEquipmentStatus[EQUIPPOS_HEAD];
					EnduStrippingDamage(sTargetH, sAttackerH, cAttackerType, iTemp, 3000);
					break;
				}


				if (cAttackerSA == 2 && g_clientList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT]) {
					g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_MAGICEFFECTOFF, MAGICTYPE_PROTECT, g_clientList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT], NULL, NULL);
					switch(g_clientList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT]) 
					{
					case MAGICPROTECT_PFA:
						g_clientList[sTargetH]->SetStatusFlag(STATUS_PFA, FALSE);
						break;
					case MAGICPROTECT_PFM:
					case MAGICPROTECT_AMP:
						g_clientList[sTargetH]->SetStatusFlag(STATUS_PFM, FALSE);
						break;
					case MAGICPROTECT_DS:
					case MAGICPROTECT_GDS:
						g_clientList[sTargetH]->SetStatusFlag(STATUS_DEFENSESHIELD, FALSE);
						break;
					}
					g_clientList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT] = NULL;
					g_game->RemoveFromDelayEventList(sTargetH, OWNERTYPE_PLAYER, MAGICTYPE_PROTECT);					  
				}


				if ( (g_clientList[sTargetH]->m_bIsPoisoned == FALSE) && 
					((cAttackerSA == 5) || (cAttackerSA == 6) || (cAttackerSA == 61)) ) {
						if (checkResistingPoisonSuccess(sTargetH, OWNERTYPE_PLAYER) == FALSE) {

							g_clientList[sTargetH]->m_bIsPoisoned  = TRUE;
							if (cAttackerSA == 5)		g_clientList[sTargetH]->m_iPoisonLevel = 15;
							else if (cAttackerSA == 6)  g_clientList[sTargetH]->m_iPoisonLevel = 40;
							else if (cAttackerSA == 61) g_clientList[sTargetH]->m_iPoisonLevel = iAttackerSAvalue; 

							g_clientList[sTargetH]->m_dwPoisonTime = dwTime;

							g_clientList[sTargetH]->SetStatusFlag(STATUS_POISON, TRUE);
							g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_MAGICEFFECTON, MAGICTYPE_POISON, g_clientList[sTargetH]->m_iPoisonLevel, NULL, NULL);
#ifdef TAIWANLOG
							_bItemLog(ITEMLOG_POISONED,sTargetH,(char *) NULL,NULL) ;
#endif
						}
				}

				g_clientList[sTargetH]->m_iHP -= iAP_SM;
				g_clientList[sTargetH]->m_lastDamageTime = dwTime;
				if (g_clientList[sTargetH]->m_iHP <= 0) {

					if (cAttackerType == OWNERTYPE_PLAYER)
						g_game->bAnalyzeCriminalAction(sAttackerH, g_clientList[sTargetH]->m_sX, g_clientList[sTargetH]->m_sY);

					g_clientList[sTargetH]->KilledHandler( sAttackerH, cAttackerType, iAP_SM);
					bKilled     = TRUE;
					iKilledDice = g_clientList[sTargetH]->m_iLevel;

				}
				else {
					if (iAP_SM > 0) {

						if (g_clientList[sTargetH]->m_iAddTransMana > 0) {
							dTmp1 = (double)g_clientList[sTargetH]->m_iAddTransMana;
							dTmp2 = (double)iAP_SM;
							dTmp3 = (dTmp1/100.0f)*dTmp2;


							iTemp = (2*g_clientList[sTargetH]->GetMag()) + (2*g_clientList[sTargetH]->m_iLevel) + (g_clientList[sTargetH]->GetInt()/2);
							g_clientList[sTargetH]->m_iMP += (int)dTmp3;
							if (g_clientList[sTargetH]->m_iMP > iTemp) g_clientList[sTargetH]->m_iMP = iTemp;
						}


						if (g_clientList[sTargetH]->m_iAddChargeCritical > 0) {
							if (dice(1,100) < (g_clientList[sTargetH]->m_iAddChargeCritical)) {
								iMaxSuperAttack = (g_clientList[sTargetH]->m_iLevel / 10);
								if (g_clientList[sTargetH]->m_iSuperAttackLeft < iMaxSuperAttack) g_clientList[sTargetH]->m_iSuperAttackLeft++;

								g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
							}
						}

						g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_HP, NULL, NULL, NULL, NULL);

						if (cAttackerType == OWNERTYPE_PLAYER) 
							sAttackerWeapon = ((g_clientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);
						else sAttackerWeapon = 1;


						if ((cAttackerType == OWNERTYPE_PLAYER) && (g_mapList[g_clientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone == TRUE)) 
							iMoveDamage = 60;
						else iMoveDamage = 40;

						if (iAP_SM >= iMoveDamage) {

							if (sTgtX == sAtkX) {
								if (sTgtY == sAtkY)     goto CAE_SKIPDAMAGEMOVE;
								else if (sTgtY > sAtkY) cDamageMoveDir = 5;
								else if (sTgtY < sAtkY) cDamageMoveDir = 1;
							}
							else if (sTgtX > sAtkX) {
								if (sTgtY == sAtkY)     cDamageMoveDir = 3;
								else if (sTgtY > sAtkY) cDamageMoveDir = 4;
								else if (sTgtY < sAtkY) cDamageMoveDir = 2;
							}
							else if (sTgtX < sAtkX) {
								if (sTgtY == sAtkY)     cDamageMoveDir = 7;
								else if (sTgtY > sAtkY) cDamageMoveDir = 6;
								else if (sTgtY < sAtkY) cDamageMoveDir = 8;
							}


							g_clientList[sTargetH]->m_iLastDamage = iAP_SM;

							g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_DAMAGEMOVE, cDamageMoveDir, iAP_SM, sAttackerWeapon, NULL);
						}
						else {
CAE_SKIPDAMAGEMOVE:;
							int iProb;


							//if (cAttackerType == OWNERTYPE_PLAYER) {
							//	switch (g_clientList[sAttackerH]->m_sUsingWeaponSkill) {
							//	case SKILL_ARCHERY: iProb = 3500; break;
							//	case SKILL_LONGSWORD: iProb = 1000; break;
							//	case SKILL_FENCING: iProb = 2900; break;
							//	case SKILL_AXE: iProb = 2500; break;
							//	case SKILL_HAMMER: iProb = 2000; break;
							//	case SKILL_STAFF: iProb = 2000; break;
							//	default: iProb = 1; break;
							//	}
							//}
							//else 
								iProb = 500;//1

							if (dice(1,10000) >= iProb) 
								g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_PLAYER, MSGID_EVENT_MOTION, OBJECTDAMAGE, iAP_SM, sAttackerWeapon, NULL);
						}

						if (g_clientList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] == 1) {

							// 1: Hold-Person 
							// 2: Paralize
							g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_MAGICEFFECTOFF, MAGICTYPE_HOLDOBJECT, g_clientList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ], NULL, NULL);

							g_clientList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] = NULL;
							g_game->RemoveFromDelayEventList(sTargetH, OWNERTYPE_PLAYER, MAGICTYPE_HOLDOBJECT);
						}

						g_clientList[sTargetH]->m_iSuperAttackCount++;
						if (g_clientList[sTargetH]->m_iSuperAttackCount > 14) {

							g_clientList[sTargetH]->m_iSuperAttackCount = 0;
							iMaxSuperAttack = (g_clientList[sTargetH]->m_iLevel / 10);
							if (g_clientList[sTargetH]->m_iSuperAttackLeft < iMaxSuperAttack) g_clientList[sTargetH]->m_iSuperAttackLeft++;

							g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_SUPERATTACKLEFT, NULL, NULL, NULL, NULL);
						}
					}
				}
			}
			break;				   

		case OWNERTYPE_NPC:

			if (g_npcList[sTargetH]->m_cBehavior == BEHAVIOR_DEAD) return 0;
			if (g_npcList[sTargetH]->m_bIsKilled == TRUE) return 0;

			if (g_game->m_bIsCrusadeMode == TRUE) {
				if (cAttackerSide == g_npcList[sTargetH]->m_side) {
					switch (g_npcList[sTargetH]->m_sType) {
					case NPC_ESG:
					case NPC_GMG:
					case NPC_LWB:
					case NPC_GHK:
					case NPC_GHKABS:
					case NPC_TK:
					case NPC_BG: 
					case NPC_CP:
						return 0;

					default: break;
					}
				}
				else {
					switch (g_npcList[sTargetH]->m_sType) {
					case NPC_GMG:
						if (cAttackerSide != 0) {
							g_npcList[sTargetH]->m_iV1 += iAP_L;
							if (g_npcList[sTargetH]->m_iV1 > 500) {

								g_npcList[sTargetH]->m_iV1 = 0;
								g_game->m_mana[g_npcList[sTargetH]->m_side]--;
								if (g_game->m_mana[g_npcList[sTargetH]->m_side] <= 0) g_game->m_mana[g_npcList[sTargetH]->m_side] = 0;
								//testcode
								wsprintf(g_cTxt, "ManaStock down: %d", g_game->m_mana[g_npcList[sTargetH]->m_side]);
								PutLogList(g_cTxt);
							}
						}
						break;
					}
				}
			}

			switch (g_npcList[sTargetH]->m_cActionLimit) 
			{
			case 1:
			case 2:
			case 6: 
				return 0;
			}

			if (g_npcList[sTargetH]->m_cSize == 0)
				iDamage = iAP_SM;
			else iDamage = iAP_L;

			if (g_npcList[sTargetH]->m_iAbsDamage < 0) {
				dTmp1 = (double)iDamage;
				dTmp2 = (double)(abs(g_npcList[sTargetH]->m_iAbsDamage))/100.0f;
				dTmp3 = dTmp1 * dTmp2;
				dTmp2 = dTmp1 - dTmp3;
				iDamage = (int)dTmp2;
				if (iDamage < 0) iDamage = 1;
			}


			if (cAttackerSA == 2 && g_npcList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT]) {
				switch(g_npcList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT]) 
				{
				case MAGICPROTECT_PFA:
					g_npcList[sTargetH]->SetStatusFlag(STATUS_PFA, FALSE);
					break;
				case MAGICPROTECT_PFM:
				case MAGICPROTECT_AMP:
					g_npcList[sTargetH]->SetStatusFlag(STATUS_PFM, FALSE);
					break;
				case MAGICPROTECT_DS:
				case MAGICPROTECT_GDS:
					g_npcList[sTargetH]->SetStatusFlag(STATUS_DEFENSESHIELD, FALSE);
					break;
				}
				g_npcList[sTargetH]->m_cMagicEffectStatus[MAGICTYPE_PROTECT] = NULL;
				g_game->RemoveFromDelayEventList(sTargetH, OWNERTYPE_NPC, MAGICTYPE_PROTECT);					  
			}


			switch (g_npcList[sTargetH]->m_cActionLimit) 
			{
			case 0: 		
			case 3: 
			case 5: 
				g_npcList[sTargetH]->m_iHP -= iDamage;
				break;
			}

			if (g_npcList[sTargetH]->m_iHP <= 0) {

				g_game->NpcKilledHandler(sAttackerH, cAttackerType, sTargetH, iDamage);

				bKilled = TRUE;
				iKilledDice = g_npcList[sTargetH]->m_iHitDice;

			}
			else {

				if ((g_npcList[sTargetH]->m_sType != 21) && (g_npcList[sTargetH]->m_sType != 55) && (g_npcList[sTargetH]->m_sType != 56)
					&& (g_npcList[sTargetH]->m_side == cAttackerSide)) goto CAE_SKIPCOUNTERATTACK;


				if (g_npcList[sTargetH]->m_cActionLimit != 0) goto CAE_SKIPCOUNTERATTACK;
				if (g_npcList[sTargetH]->m_bIsPermAttackMode == TRUE) goto CAE_SKIPCOUNTERATTACK;
				if ((g_npcList[sTargetH]->m_bIsSummoned == TRUE) && 
					(g_npcList[sTargetH]->m_iSummonControlMode == 1)) goto CAE_SKIPCOUNTERATTACK;

				if (g_npcList[sTargetH]->m_sType == NPC_CP) goto CAE_SKIPCOUNTERATTACK;

				if (dice(1,3) == 2) {

					if (g_npcList[sTargetH]->m_cBehavior == BEHAVIOR_ATTACK) {
						tX = tY = 0;
						switch (g_npcList[sTargetH]->m_cTargetType) {
						case OWNERTYPE_PLAYER:
							if (g_clientList[g_npcList[sTargetH]->m_iTargetIndex] != NULL) {
								tX = g_clientList[g_npcList[sTargetH]->m_iTargetIndex]->m_sX;
								tY = g_clientList[g_npcList[sTargetH]->m_iTargetIndex]->m_sY;
							}
							break;

						case OWNERTYPE_NPC:
							if (g_npcList[g_npcList[sTargetH]->m_iTargetIndex] != NULL) {
								tX = g_npcList[g_npcList[sTargetH]->m_iTargetIndex]->m_sX;
								tY = g_npcList[g_npcList[sTargetH]->m_iTargetIndex]->m_sY;
							}
							break;
						}
						iDst1 = (g_npcList[sTargetH]->m_sX - tX)*(g_npcList[sTargetH]->m_sX - tX) + (g_npcList[sTargetH]->m_sY - tY)*(g_npcList[sTargetH]->m_sY - tY);

						tX = tY = 0;
						switch (cAttackerType) {
						case OWNERTYPE_PLAYER:
							if (g_clientList[sAttackerH] != NULL) {
								tX = g_clientList[sAttackerH]->m_sX;
								tY = g_clientList[sAttackerH]->m_sY;
							}
							break;

						case OWNERTYPE_NPC:
							if (g_npcList[sAttackerH] != NULL) {
								tX = g_npcList[sAttackerH]->m_sX;
								tY = g_npcList[sAttackerH]->m_sY;
							}
							break;
						}


						iDst2 = (g_npcList[sTargetH]->m_sX - tX)*(g_npcList[sTargetH]->m_sX - tX) + (g_npcList[sTargetH]->m_sY - tY)*(g_npcList[sTargetH]->m_sY - tY);

						if (iDst2 <= iDst1) {

							g_npcList[sTargetH]->m_cBehavior          = BEHAVIOR_ATTACK;
							g_npcList[sTargetH]->m_sBehaviorTurnCount = 0;
							g_npcList[sTargetH]->m_iTargetIndex = sAttackerH;
							g_npcList[sTargetH]->m_cTargetType  = cAttackerType;
						}
					}
					else {
						g_npcList[sTargetH]->m_cBehavior          = BEHAVIOR_ATTACK;
						g_npcList[sTargetH]->m_sBehaviorTurnCount = 0;
						g_npcList[sTargetH]->m_iTargetIndex = sAttackerH;
						g_npcList[sTargetH]->m_cTargetType  = cAttackerType;
					}
				}

CAE_SKIPCOUNTERATTACK:;


				// Stun
				if ((dice(1, (g_npcList[sTargetH]->dwGoldDropValue / 55) + 3 ) == 1) && 
					(g_npcList[sTargetH]->m_cActionLimit == 0))
					g_npcList[sTargetH]->m_dwTime = dwTime;


				if (cAttackerType == OWNERTYPE_PLAYER) 
					sAttackerWeapon = ((g_clientList[sAttackerH]->m_sAppr2 & 0x0FF0) >> 4);
				else sAttackerWeapon = 1;

				if ((wWeaponType < 40) && (g_npcList[sTargetH]->m_cActionLimit == 4)) {

					if (sTgtX == sAtkX) {
						if (sTgtY == sAtkY)     goto CAE_SKIPDAMAGEMOVE2;
						else if (sTgtY > sAtkY) cDamageMoveDir = 5;
						else if (sTgtY < sAtkY) cDamageMoveDir = 1;
					}
					else if (sTgtX > sAtkX) {
						if (sTgtY == sAtkY)     cDamageMoveDir = 3;
						else if (sTgtY > sAtkY) cDamageMoveDir = 4;
						else if (sTgtY < sAtkY) cDamageMoveDir = 2;
					}
					else if (sTgtX < sAtkX) {
						if (sTgtY == sAtkY)     cDamageMoveDir = 7;
						else if (sTgtY > sAtkY) cDamageMoveDir = 6;
						else if (sTgtY < sAtkY) cDamageMoveDir = 8;
					}

					dX = g_npcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
					dY = g_npcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

					if (g_mapList[g_npcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) {

						cDamageMoveDir = dice(1,8);
						dX = g_npcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
						dY = g_npcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

						if (g_mapList[g_npcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) goto CAE_SKIPDAMAGEMOVE2;
					}

					g_mapList[g_npcList[sTargetH]->m_cMapIndex]->ClearOwner(/*5,*/ sTargetH, OWNERTYPE_NPC, g_npcList[sTargetH]->m_sX, g_npcList[sTargetH]->m_sY);

					g_mapList[g_npcList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, OWNERTYPE_NPC, dX, dY);
					g_npcList[sTargetH]->m_sX   = dX;
					g_npcList[sTargetH]->m_sY   = dY;
					g_npcList[sTargetH]->m_cDir = cDamageMoveDir;

					g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTMOVE, NULL, NULL, NULL);

					dX = g_npcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
					dY = g_npcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

					if (g_mapList[g_npcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) {

						cDamageMoveDir = dice(1,8);
						dX = g_npcList[sTargetH]->m_sX + _tmp_cTmpDirX[cDamageMoveDir];
						dY = g_npcList[sTargetH]->m_sY + _tmp_cTmpDirY[cDamageMoveDir];

						if (g_mapList[g_npcList[sTargetH]->m_cMapIndex]->bGetMoveable(dX, dY, NULL) == FALSE) goto CAE_SKIPDAMAGEMOVE2;
					}

					g_mapList[g_npcList[sTargetH]->m_cMapIndex]->ClearOwner(/*5,*/ sTargetH, OWNERTYPE_NPC, g_npcList[sTargetH]->m_sX, g_npcList[sTargetH]->m_sY);

					g_mapList[g_npcList[sTargetH]->m_cMapIndex]->SetOwner(sTargetH, OWNERTYPE_NPC, dX, dY);
					g_npcList[sTargetH]->m_sX   = dX;
					g_npcList[sTargetH]->m_sY   = dY;
					g_npcList[sTargetH]->m_cDir = cDamageMoveDir;

					g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTMOVE, NULL, NULL, NULL);

					if (g_game->bCheckEnergySphereDestination(sTargetH, sAttackerH, cAttackerType) == TRUE) {
						if (cAttackerType == OWNERTYPE_PLAYER) {
							iExp = (g_npcList[sTargetH]->m_iExp/3);
							if (g_npcList[sTargetH]->m_iNoDieRemainExp > 0)
								iExp += g_npcList[sTargetH]->m_iNoDieRemainExp;


							if (g_clientList[sAttackerH]->m_iAddExp != NULL) {
								dTmp1 = (double)g_clientList[sAttackerH]->m_iAddExp;
								dTmp2 = (double)iExp;
								dTmp3 = (dTmp1/100.0f)*dTmp2;
								iExp += (int)dTmp3;
							}

							// Crusade
							if ((g_game->m_bIsCrusadeMode == TRUE) && (iExp > 10)) iExp = 10;

							//g_clientList[sAttackerH]->m_iExpStock += iExp;
							g_game->GetExp(sAttackerH, iExp);


							g_game->DeleteNpc(sTargetH);
							return FALSE;
						}
					}

CAE_SKIPDAMAGEMOVE2:;
				}
				else {
					g_game->SendEventToNearClient_TypeA(sTargetH, OWNERTYPE_NPC, MSGID_EVENT_MOTION, OBJECTDAMAGE, iDamage, sAttackerWeapon, NULL);
				}

				if (g_npcList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] == 1) {

					// 1: Hold-Person 
					g_npcList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] = NULL;
					g_game->RemoveFromDelayEventList(sTargetH, OWNERTYPE_NPC, MAGICTYPE_HOLDOBJECT);
				}
				else if (g_npcList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] == 2) {
					// 2: Paralize
					if ((g_npcList[sTargetH]->m_iHitDice > 50) && (dice(1, 10) == 5)) {
						g_npcList[sTargetH]->m_cMagicEffectStatus[ MAGICTYPE_HOLDOBJECT ] = NULL;
						g_game->RemoveFromDelayEventList(sTargetH, OWNERTYPE_NPC, MAGICTYPE_HOLDOBJECT);
					}
				}


				if ( (g_npcList[sTargetH]->m_iNoDieRemainExp > 0) && (g_npcList[sTargetH]->m_bIsSummoned != TRUE) && 
					(cAttackerType == OWNERTYPE_PLAYER) && (g_clientList[sAttackerH] != NULL) ) {


						if (g_npcList[sTargetH]->m_iNoDieRemainExp > iDamage) {
							iExp = iDamage;
							g_npcList[sTargetH]->m_iNoDieRemainExp -= iDamage;
						}
						else {
							iExp = g_npcList[sTargetH]->m_iNoDieRemainExp;
							g_npcList[sTargetH]->m_iNoDieRemainExp = 0;
						}


						if (g_clientList[sAttackerH]->m_iAddExp != NULL) {
							dTmp1 = (double)g_clientList[sAttackerH]->m_iAddExp;
							dTmp2 = (double)iExp;
							dTmp3 = (dTmp1/100.0f)*dTmp2;
							iExp += (int)dTmp3;
						}

						if (g_game->m_bIsCrusadeMode == TRUE) iExp = iExp/3;


						if (g_clientList[sAttackerH]->m_iLevel > 100 ) {
							switch (g_npcList[sTargetH]->m_sType) {
							case 55:
							case 56:
								iExp = 0 ;
								break ;
							default: break;
							}
						}

				}
			}
			break;
		}

		//CAE_SKIPCOUNTERATTACK:;

		if (cAttackerType == OWNERTYPE_PLAYER) {

			if (g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND] != -1)
				sWeaponIndex = g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND];
			else sWeaponIndex = g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_RHAND];

			if (sWeaponIndex != -1) {
				if ( (g_clientList[sAttackerH]->m_pItemList[sWeaponIndex] != NULL) &&
					(g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_sIDnum != ITEM_PICKAXE) ) {
						if (bKilled == FALSE)
							CalculateSSN_ItemIndex(sAttackerH, sWeaponIndex, 1);
						else {
							if (g_clientList[sAttackerH]->m_iHP <= 3) 
								CalculateSSN_ItemIndex(sAttackerH, sWeaponIndex, dice(1, iKilledDice)*2);
							else CalculateSSN_ItemIndex(sAttackerH, sWeaponIndex, dice(1, iKilledDice));
						}
				}

				if ( (g_clientList[sAttackerH]->m_pItemList[sWeaponIndex] != NULL) && 
					(g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wMaxLifeSpan != 0) ) 
				{
						iWepLifeOff = 1;
						if ((wWeaponType >= 1) && (wWeaponType < 40)) {
							switch (g_mapList[g_clientList[sAttackerH]->m_cMapIndex]->m_cWhetherStatus) {
							case 0:	break;
							case 1:	if (dice(1,3) == 1) iWepLifeOff++; break;
							case 2:	if (dice(1,2) == 1) iWepLifeOff += dice(1,2); break;
							case 3:	if (dice(1,2) == 1) iWepLifeOff += dice(1,3); break;
							}
						}

						if (!g_clientList[sAttackerH]->IsNeutral()) {
							if (g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan < iWepLifeOff) 
								g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan = 0;
							else g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan -= iWepLifeOff;
						}

						if (g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_wCurLifeSpan == 0) {

							g_game->SendNotifyMsg(NULL, sAttackerH, NOTIFY_ITEMLIFESPANEND, g_clientList[sAttackerH]->m_pItemList[sWeaponIndex]->m_cEquipPos, sWeaponIndex, NULL, NULL);

							g_game->ReleaseItemHandler(sAttackerH, sWeaponIndex, TRUE);  
						}
				}
			}
			else {
				/*if (wWeaponType == 0) {
					CalculateSSN_SkillIndex(sAttackerH, SKILL_HANDATTACK, 1);
				}*/
			}
		}
	}
	else {
		if (cAttackerType == OWNERTYPE_PLAYER) {
			g_clientList[sAttackerH]->m_iComboAttackCount = 0;
		}
	}

	return iExp;
}

void EnduStrippingDamage(short sTargetH, short sAttackerH, char cAttackerType, int item, int higherStripEndu)
{
	int equiptItem, enduDamage = 1;
	float stripChance = 0;

	if (g_clientList[sTargetH] == NULL) return;
	if (cAttackerType	== OWNERTYPE_PLAYER && g_clientList[sAttackerH] == NULL) return;
	if (item == -1 || g_clientList[sTargetH]->m_pItemList[item] == NULL) return;

	if (cAttackerType	== OWNERTYPE_PLAYER && 
		(g_clientList[sTargetH]->m_side != g_clientList[sAttackerH]->m_side || g_mapList[g_clientList[sAttackerH]->m_cMapIndex]->m_bIsFightZone)){
		//switch (g_clientList[sAttackerH]->m_sUsingWeaponSkill) {
		////case SKILL_HAMMER:
		//	stripChance = 0.25;
		//	enduDamage = 20;
		//	equiptItem = g_clientList[sAttackerH]->m_sItemEquipmentStatus[EQUIPPOS_TWOHAND];
		//	if (equiptItem == -1 || g_clientList[sAttackerH]->m_pItemList[equiptItem] == NULL) break;

		//	switch (g_clientList[sAttackerH]->m_pItemList[equiptItem]->m_sIDnum){
		//	case ITEM_HAMMER:
		//		stripChance = 0.25;
		//		enduDamage = 20;
		//		break;
		//	case ITEM_BHAMMER:
		//		stripChance = 0.5; 
		//		enduDamage = 25;
		//		break;
		//	case ITEM_BARBARIANHAMMER:
		//		stripChance = 0.625;
		//		enduDamage = 30;
		//		break;
		//	case ITEM_GBHAMMER:
		//		stripChance = 0.625; 
		//		enduDamage = 35;
		//		break;
		//	}
		//	break;
		////case SKILL_AXE: enduDamage = 3; break;  
		//default: enduDamage = 1; break;  
		//}
	}

	if (!g_clientList[sTargetH]->IsNeutral() && 
		g_clientList[sTargetH]->m_pItemList[item]->m_wCurLifeSpan > 0 &&
		memcmp(g_clientList[sTargetH]->m_pItemList[item]->m_cName, "Legion", 6) != 0) {
		g_clientList[sTargetH]->m_pItemList[item]->m_wCurLifeSpan -= enduDamage; 
	}

	if (g_clientList[sTargetH]->m_pItemList[item]->m_wCurLifeSpan <= 0) {
		g_clientList[sTargetH]->m_pItemList[item]->m_wCurLifeSpan = 0 ;
		g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_ITEMLIFESPANEND, g_clientList[sTargetH]->m_pItemList[item]->m_cEquipPos, item, NULL, NULL);
		g_game->ReleaseItemHandler(sTargetH, item, TRUE);  
	}
	else if (stripChance > 0) {
		switch (g_clientList[sTargetH]->m_pItemList[item]->m_sIDnum) {
		case ITEM_MERIENPLATEMAIL_M: 
		case ITEM_MERIENPLATEMAIL_W: 
			return;
		}

		if ( g_clientList[sTargetH]->m_pItemList[item]->m_wMaxLifeSpan <  higherStripEndu )
			stripChance *= dice(6, (g_clientList[sTargetH]->m_pItemList[item]->m_wMaxLifeSpan - g_clientList[sTargetH]->m_pItemList[item]->m_wCurLifeSpan));
		else 
			stripChance *= dice(4, (g_clientList[sTargetH]->m_pItemList[item]->m_wMaxLifeSpan - g_clientList[sTargetH]->m_pItemList[item]->m_wCurLifeSpan));

		if (stripChance >  g_clientList[sTargetH]->m_pItemList[item]->m_wCurLifeSpan) {
			g_game->ReleaseItemHandler(sTargetH, item, TRUE);  
			g_game->SendNotifyMsg(NULL, sTargetH, NOTIFY_ITEMRELEASED, g_clientList[sTargetH]->m_pItemList[item]->m_cEquipPos, item, NULL, NULL);
		}
	}
}