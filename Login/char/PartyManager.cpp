// PartyManager.cpp: implementation of the PartyManager class.
//
//////////////////////////////////////////////////////////////////////

#include "PartyManager.h"

extern char G_cTxt[120];
extern void PutLogList(char * cMsg);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PartyManager::PartyManager(class CLoginServer * pGateCore)
{
 int i;

	for (i = 0; i < MAXPARTY; i++) {
		m_iMemberNumList[i] = NULL;
		m_stMemberNameList[i].m_iPartyID = NULL;
		m_stMemberNameList[i].m_iIndex = NULL;
		m_stMemberNameList[i].m_dwServerChangeTime = NULL;
		ZeroMemory(m_stMemberNameList[i].m_cName, sizeof(m_stMemberNameList[i].m_cName)); 
	}

	m_pGateCore = pGateCore;
	m_dwCheckMemberActTime = timeGetTime();
}

PartyManager::~PartyManager()
{

}

int PartyManager::iCreateNewParty(int iClientH, char *pMasterName)
{
	int i, iPartyID;

	for (i = 1; i < MAXPARTY; i++) 
	if ((m_stMemberNameList[i].m_iPartyID != NULL) && (strcmp(m_stMemberNameList[i].m_cName, pMasterName) == 0)) return 0;

	iPartyID = 0;
	for (i = 1; i < MAXPARTY; i++)
	if (m_iMemberNumList[i] == NULL) {
		iPartyID = i;
		m_iMemberNumList[iPartyID]++;
		goto CNP_BREAKLOOP;
	}
	
	return 0;

CNP_BREAKLOOP:;
	for (i = 1; i < MAXPARTY; i++) 
	if (m_stMemberNameList[i].m_iPartyID == NULL) {
		m_stMemberNameList[i].m_iPartyID = iPartyID;
		ZeroMemory(m_stMemberNameList[i].m_cName, sizeof(m_stMemberNameList[i].m_cName));
		strcpy(m_stMemberNameList[i].m_cName, pMasterName);
		m_stMemberNameList[i].m_iIndex = iClientH;
		
		return iPartyID;
	}

	return 0;
}

BOOL PartyManager::bDeleteParty(int iPartyID)
{
 int i;
 BOOL bFlag;
 char * cp, cData[120];
 DWORD * dwp;
 WORD * wp;

	bFlag = FALSE;
	m_iMemberNumList[iPartyID] = NULL;

	for (i = 1; i < MAXPARTY; i++)
	if (m_stMemberNameList[i].m_iPartyID == iPartyID) {
		m_stMemberNameList[i].m_iPartyID = NULL;
		m_stMemberNameList[i].m_iIndex = NULL;
		m_stMemberNameList[i].m_dwServerChangeTime = NULL;
		ZeroMemory(m_stMemberNameList[i].m_cName, sizeof(m_stMemberNameList[i].m_cName));
		bFlag = TRUE;
	}

	ZeroMemory(cData, sizeof(cData));
	cp = (char *)cData;
	dwp = (DWORD *)cp;
	*dwp = MSGID_PARTYOPERATION;
	cp += 4;
	wp = (WORD *)cp;
	*wp = 2;
	cp += 2; 
	wp = (WORD *)cp;
	*wp = iPartyID;
	cp += 2;
	m_pGateCore->SendMsgToAllGameServers(NULL, cData, 10, TRUE);

	return bFlag;
}

BOOL PartyManager::bAddMember(int iClientH, int iPartyID, char *pMemberName)
{
 int i;


	if (m_iMemberNumList[iPartyID] >= MAXPARTYMEMBERS) return FALSE;

	for (i = 1; i < MAXPARTY; i++)
		if ((m_stMemberNameList[i].m_iPartyID != NULL) && (strcmp(m_stMemberNameList[i].m_cName, pMemberName) == 0))
		{
			m_stMemberNameList[i].m_iPartyID = NULL;
			m_stMemberNameList[i].m_iIndex = NULL;
			m_stMemberNameList[i].m_dwServerChangeTime = NULL;
			ZeroMemory(m_stMemberNameList[i].m_cName, sizeof(m_stMemberNameList[i].m_cName));
			
			m_iMemberNumList[iPartyID]--;
			if (m_iMemberNumList[iPartyID] <= 1) bDeleteParty(iPartyID);
		}
//		return FALSE;

	
	for (i = 1; i < MAXPARTY; i++)
	if (m_stMemberNameList[i].m_iPartyID == NULL) {
		m_stMemberNameList[i].m_iPartyID = iPartyID;
		m_stMemberNameList[i].m_iIndex = iClientH;
		m_stMemberNameList[i].m_dwServerChangeTime = NULL;
		ZeroMemory(m_stMemberNameList[i].m_cName, sizeof(m_stMemberNameList[i].m_cName));
		strcpy(m_stMemberNameList[i].m_cName, pMemberName);
		m_iMemberNumList[iPartyID]++;

		return TRUE;
	}

	return FALSE;
}

BOOL PartyManager::bRemoveMember(int iPartyID, char *pMemberName)
{
 int i;

	for (i = 1; i < MAXPARTY; i++)
	if ((m_stMemberNameList[i].m_iPartyID == iPartyID) && (strcmp(m_stMemberNameList[i].m_cName, pMemberName) == 0)) {

		m_stMemberNameList[i].m_iPartyID = NULL;
		m_stMemberNameList[i].m_iIndex = NULL;
		m_stMemberNameList[i].m_dwServerChangeTime = NULL;
		ZeroMemory(m_stMemberNameList[i].m_cName, sizeof(m_stMemberNameList[i].m_cName));
		
		m_iMemberNumList[iPartyID]--;
		if (m_iMemberNumList[iPartyID] <= 1) bDeleteParty(iPartyID);

		return TRUE;
	}

	return FALSE;
}


BOOL PartyManager::bCheckPartyMember(int iClientH, int iGSCH, int iPartyID, char *pName)
{
 int i;
 char * cp, cData[120];
 DWORD * dwp;
 WORD * wp;

	for (i = 1; i < MAXPARTY; i++)
	if ((m_stMemberNameList[i].m_iPartyID == iPartyID) && (strcmp(m_stMemberNameList[i].m_cName, pName) == 0)) {
		m_stMemberNameList[i].m_dwServerChangeTime = NULL;
		return TRUE;
	}

	ZeroMemory(cData, sizeof(cData));
	cp = (char *)cData;
	dwp = (DWORD *)cp;
	*dwp = MSGID_PARTYOPERATION;
	cp += 4;
	wp = (WORD *)cp;
	*wp = 3;
	cp += 2; 
	wp = (WORD *)cp;
	*wp = iGSCH;
	cp += 2;
	memcpy(cp, pName, 10);
	cp += 10;
	m_pGateCore->SendMsgToGS(iClientH, cData, 20);
	
	return FALSE;
}

BOOL PartyManager::bGetPartyInfo(int iClientH, int iGSCH, char * pName, int iPartyID)
{
 int i, iTotal;
 char * cp, cData[1024];
 DWORD * dwp;
 WORD * wp, * wpTotal;

	ZeroMemory(cData, sizeof(cData));
	cp = (char *)cData;
	dwp = (DWORD *)cp;
	*dwp = MSGID_PARTYOPERATION;
	cp += 4;
	wp = (WORD *)cp;
	*wp = 5;
	cp += 2; 
	wp = (WORD *)cp;
	*wp = iGSCH;
	cp += 2;
	memcpy(cp, pName, 10);
	cp += 10;
	wp = (WORD *)cp;
	wpTotal = wp;
	cp += 2;

	iTotal = 0;
	for (i = 1; i < MAXPARTY; i++)
	if ((m_stMemberNameList[i].m_iPartyID == iPartyID) && (m_stMemberNameList[i].m_iPartyID != NULL)) {
		memcpy(cp, m_stMemberNameList[i].m_cName, 10);
		cp += 11;
		iTotal++;
	}
	
	*wpTotal = iTotal;
	m_pGateCore->SendMsgToGS(iClientH, cData, 20 + iTotal*11 +1);

	return TRUE;
}

void PartyManager::GameServerDown(int iClientH)
{
 int i;

	for (i = 0; i < MAXPARTY; i++)
	if (m_stMemberNameList[i].m_iIndex == iClientH) {

		m_iMemberNumList[m_stMemberNameList[i].m_iPartyID]--;
		m_stMemberNameList[i].m_iPartyID  = NULL;
		m_stMemberNameList[i].m_iIndex    = NULL;
		m_stMemberNameList[i].m_dwServerChangeTime = NULL;
		ZeroMemory(m_stMemberNameList[i].m_cName, sizeof(m_stMemberNameList[i].m_cName));
	}
}

void PartyManager::SetServerChangeStatus(char *pName, int iPartyID)
{
 int i;

	for (i = 1; i < MAXPARTY; i++)
	if ((m_stMemberNameList[i].m_iPartyID == iPartyID) && (strcmp(m_stMemberNameList[i].m_cName, pName) == 0)) {
		m_stMemberNameList[i].m_dwServerChangeTime = timeGetTime();
		return;
	}
}

void PartyManager::CheckMemberActivity()
{
 int i;
 DWORD * dwp, dwTime = timeGetTime();
 char * cp, cData[120];
 WORD * wp;

	if ((dwTime - m_dwCheckMemberActTime) > 1000*2) {
		m_dwCheckMemberActTime = dwTime;
	} else return;

	for (i = 1; i < MAXPARTY; i++)
	if ((m_stMemberNameList[i].m_dwServerChangeTime != NULL) && ((dwTime - m_stMemberNameList[i].m_dwServerChangeTime) > 1000*20)) {
		ZeroMemory(cData, sizeof(cData));
		cp = (char *)cData;
		dwp = (DWORD *)cp;
		*dwp = MSGID_PARTYOPERATION;
		cp += 4;
		wp = (WORD *)cp;
		*wp = 6;
		cp += 2;
		*cp = 1;
		cp++;
		wp = (WORD *)cp;
		*wp = NULL;  
		cp += 2;
		memcpy(cp, m_stMemberNameList[i].m_cName, 10);
		cp += 10;
		wp = (WORD *)cp;
		*wp = (WORD)m_stMemberNameList[i].m_iPartyID;
		cp += 2;
		m_pGateCore->SendMsgToAllGameServers(NULL, cData, 22, TRUE);

		bRemoveMember(m_stMemberNameList[i].m_iPartyID, m_stMemberNameList[i].m_cName);
	}
}
