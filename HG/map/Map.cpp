// Map.cpp: implementation of the CMap class.
//
//////////////////////////////////////////////////////////////////////

#include "Map.h"
#include "..\char\Unit.h"
#include "..\char\Client.h"
#include "..\char\Npc.h"


extern class CClient ** g_clientList;
extern class CNpc **	g_npcList;

extern void PutLogFileList(char * cStr);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMap::CMap(class CGame * pGame)
{
	int i, ix, iy;

	for (i = 0; i < MAXTELEPORTLOC; i++)
		m_pTeleportLoc[i] = NULL;

	for (i = 0; i < MAXWAYPOINTCFG; i++) {
		m_WaypointList[i].x = -1;
		m_WaypointList[i].y = -1;
	}

	for (i = 0; i < MAXMGAR; i++) {
		m_rcMobGenAvoidRect[i].top  = -1;
		m_rcMobGenAvoidRect[i].left = -1;
	}

	for (i = 0; i < MAXNMR; i++) {
		m_rcNoAttackRect[i].top  = -1;
		m_rcNoAttackRect[i].left = -1;
	}

	for (i = 0; i < MAXSPOTMOBGENERATOR; i++) {
		m_stSpotMobGenerator[i].bDefined = FALSE;
		m_stSpotMobGenerator[i].iTotalActiveMob = 0;
	}

	for (i = 0; i < MAXFISHPOINT; i++) {
		m_FishPointList[i].x = -1;
		m_FishPointList[i].y = -1;
	}

	for (i = 0; i < MAXMINERALPOINT; i++) {
		m_MineralPointList[i].x = -1;
		m_MineralPointList[i].y = -1;
	}

	for (i = 0; i < MAXINITIALPOINT; i++) {
		m_pInitialPoint[i].x = -1;
		m_pInitialPoint[i].y = -1;
	}
 
	for (i = 0; i < 1000; i++)
		m_bNamingValueUsingStatus[i] = FALSE;

	for (i = 0; i < MAXOCCUPYFLAG; i++)
		m_pOccupyFlag[i] = NULL;

	for (i = 0; i < MAXSTRATEGICPOINTS; i++)
		m_pStrategicPointList[i] = NULL;

	for (i = 0; i < MAXENERGYSPHERES; i++) {
		m_stEnergySphereCreationList[i].cType = NULL;
		m_stEnergySphereGoalList[i].cResult   = NULL;
	}

	for (i = 0; i < MAXITEMEVENTS; i++) {
		ZeroMemory(m_stItemEventList[i].cItemName, sizeof(m_stItemEventList[i].cItemName));
		m_stItemEventList[i].iAmount = 0;
		m_stItemEventList[i].iTotalNum = 0;
		m_stItemEventList[i].iCurNum = 0;
		m_stItemEventList[i].iMonth  = 0;
		m_stItemEventList[i].iDay    = 0;
	}
	m_iTotalItemEvents = 0;

	m_iTotalActiveObject = 0;
	m_iTotalAliveObject  = 0;

	m_bIsApocalypseMap		= FALSE;
	m_iApocalypseMobGenType = 0;
	m_iApocalypseBossMobNpcID = 0;

	m_cDynamicGateType = 0;


	//m_sInitialPointX = 0;
	//m_sInitialPointY = 0;

	m_bIsFixedDayMode = FALSE;
	m_bIsFixedSnowMode = FALSE ; 

	m_iTotalFishPoint = 0;
	m_iMaxFish = 0;
	m_iCurFish = 0;

	m_iTotalMineralPoint = 0;
	m_iMaxMineral = 0;
	m_iCurMineral = 0;

	m_pTile = NULL;

	m_cWhetherStatus = NULL;
	m_cType          = MAPTYPE_NORMAL;

	m_pGame = pGame;

	m_iLevelLimit = 0;
	m_iUpperLevelLimit = 0; 
	m_bMineralGenerator = FALSE;

	m_iTotalOccupyFlags = 0;

	m_bIsAttackEnabled = TRUE;
	m_cRandomMobGeneratorLevel = 0;

	for(i = 0; i < MAXMAGICTYPE; i++)
		m_magicLimited[i] = FALSE;

	m_isPartyDisabled = FALSE;
	m_isShieldDisabled = FALSE;
	m_isArmorDisabled = FALSE;
	m_isChatDisabled = FALSE;
	m_isPermIllusionOn = FALSE;

	m_bIsFightZone = FALSE;

	m_iTotalEnergySphereCreationPoint = 0;
	m_iTotalEnergySphereGoalPoint = 0;

	m_bIsEnergySphereGoalEnabled = FALSE;
	m_iCurEnergySphereGoalPointIndex = -1;

	for (ix = 0; ix < MAXSECTORS; ix++)
	for (iy = 0; iy < MAXSECTORS; iy++) {
		m_stSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stSectorInfo[ix][iy].iPlayerActivity  = 0;

		m_stTempSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stTempSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stTempSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stTempSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stTempSectorInfo[ix][iy].iPlayerActivity  = 0;
	} 

	m_iMaxNx = m_iMaxNy = m_iMaxAx = m_iMaxAy = m_iMaxEx = m_iMaxEy = m_iMaxMx = m_iMaxMy = m_iMaxPx = m_iMaxPy = 0;

	for (i = 0; i < MAXSTRIKEPOINTS; i++) {
		m_stStrikePoint[i].dX  = 0;
		m_stStrikePoint[i].dY  = 0;
		m_stStrikePoint[i].iHP = 0;
		m_stStrikePoint[i].iMapIndex = -1;
		ZeroMemory(m_stStrikePoint[i].cRelatedMapName, sizeof(m_stStrikePoint[i].cRelatedMapName));
	}
	m_iTotalStrikePoints = 0;
	m_bIsDisabled = FALSE;

	for (i = 0; i < MAXCRUSADESTRUCTURES; i++) {
		m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
	}
	m_iTotalCrusadeStructures = 0;
	m_iTotalAgriculture = 0;

	m_bIsEnergySphereAutoCreation = FALSE;

	for (i = 0; i < MAXHELDENIANDOOR; i++) {
		m_stHeldenianGateDoor[i].cDir = 0;
		m_stHeldenianGateDoor[i].dX = 0;
		m_stHeldenianGateDoor[i].dY = 0;
	}

	for (i = 0; i < MAXHELDENIANTOWER; i++) {
		m_stHeldenianTower[i].sTypeID = 0;
		m_stHeldenianTower[i].dX = 0;
		m_stHeldenianTower[i].dY = 0;
		m_stHeldenianTower[i].cSide = 0;
	}
	m_bIsHeldenianMap		= FALSE;

	sMobEventAmount = 15 ;   
}

CMap::~CMap()
{
	int i;

	if (m_pTile != NULL) 
		delete []m_pTile;
 
	for (i = 0; i < MAXTELEPORTLOC; i++)
		if (m_pTeleportLoc[i] != NULL) delete m_pTeleportLoc[i];

	for (i = 0; i < MAXOCCUPYFLAG; i++)
		if (m_pOccupyFlag[i] != NULL) delete m_pOccupyFlag[i];

	for (i = 0; i < MAXSTRATEGICPOINTS; i++)
		if (m_pStrategicPointList[i] != NULL) delete m_pStrategicPointList[i];
}

void CMap::SetOwner(short sOwner, char cOwnerClass, short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sOwner      = sOwner;
	pTile->m_cOwnerClass = cOwnerClass;
}


void CMap::SetDeadOwner(short sOwner, char cOwnerClass, short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;
 
	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sDeadOwner      = sOwner;
	pTile->m_cDeadOwnerClass = cOwnerClass;
}

void CMap::GetOwner(short * pOwner, char * pOwnerClass, short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) {
		*pOwner      = NULL;
		*pOwnerClass = NULL;
		return;
	}

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	*pOwner      = pTile->m_sOwner;
	*pOwnerClass = pTile->m_sOwner ? pTile->m_cOwnerClass : 0;

}


Unit * CMap::GetOwner(short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY))
		return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	switch(pTile->m_cOwnerClass)
	{
	case OWNERTYPE_NONE:
		break;
	case OWNERTYPE_PLAYER:
		return g_clientList[pTile->m_sOwner];
	case OWNERTYPE_NPC:
		return g_npcList[pTile->m_sOwner];
	}
	return NULL;
}

Unit * CMap::GetDeadOwner(short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY))
		return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	switch(pTile->m_cDeadOwnerClass)
	{
	case OWNERTYPE_NONE:
		break;
	case OWNERTYPE_PLAYER:
		return g_clientList[pTile->m_sDeadOwner];
	case OWNERTYPE_NPC:
		return g_npcList[pTile->m_sDeadOwner];
	}
	return NULL;
}


void CMap::GetDeadOwner(short * pOwner, char * pOwnerClass, short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) {
		*pOwner      = NULL;
		*pOwnerClass = NULL;
		return;
	}

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	*pOwner      = pTile->m_sDeadOwner;
	*pOwnerClass = pTile->m_cDeadOwnerClass;
}

 								  
bool CMap::bGetMoveable(short dX, short dY, short * pDOtype, class CItem * pTopItem) 
{
	class CTile * pTile;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);

	if (pDOtype != NULL) *pDOtype = pTile->m_sDynamicObjectType; 
	if (pTopItem != NULL) pTopItem = pTile->m_pItem[0]; 

	if (pTile->m_sOwner != NULL) return FALSE;
	if (pTile->m_bIsMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bIsTempMoveAllowed == FALSE) return FALSE;

	return TRUE;
}

bool CMap::bGetIsMoveAllowedTile(short dX, short dY)
{
	class CTile * pTile;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);

	if (pTile->m_bIsMoveAllowed == FALSE) return FALSE;
	if (pTile->m_bIsTempMoveAllowed == FALSE) return FALSE;

	return TRUE;
}

bool CMap::bGetIsMoveAllowedTile(Point p)
{
	if (p.x < 20 || p.x >= m_sSizeX - 20 
		|| p.y < 20 || p.y >= m_sSizeY - 20
		) return FALSE;

	CTile * pTile = (CTile *)(m_pTile + p.x + p.y*m_sSizeY);

	if (!pTile->m_bIsMoveAllowed || !pTile->m_bIsTempMoveAllowed) 
		return FALSE;

	return TRUE;
}

bool CMap::bGetIsTeleport(short dX, short dY)
{
	class CTile * pTile;

	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);

	if (pTile->m_bIsTeleport == FALSE) return FALSE;

	return TRUE;
}

void CMap::ClearOwner(/*int iDebugCode,*/ short sOwnerH, char cOwnerType, short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	if ((pTile->m_sOwner == sOwnerH) && (pTile->m_cOwnerClass == cOwnerType)) {
		pTile->m_sOwner      = NULL;
		pTile->m_cOwnerClass = NULL;
	}

	// 
	if ((pTile->m_sDeadOwner == sOwnerH) && (pTile->m_cDeadOwnerClass == cOwnerType)) {
		pTile->m_sDeadOwner      = NULL;
		pTile->m_cDeadOwnerClass = NULL;
	}
}

void CMap::ClearDeadOwner(short sX, short sY)
{
	class CTile * pTile;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pTile->m_sDeadOwner      = NULL;
	pTile->m_cDeadOwnerClass = NULL;
}

bool CMap::bSetItem(short sX, short sY, class CItem * pItem)
{
	class CTile * pTile;
	register int i;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return FALSE; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	if(pTile->m_pItem[0] && pTile->m_pItem[0]->m_sIDnum == ITEM_RELIC) return FALSE;

	if (pTile->m_pItem[ITEMS_PER_TILE-1] != NULL) 
		delete pTile->m_pItem[ITEMS_PER_TILE-1];
	else pTile->m_cTotalItem++;

	for (i = ITEMS_PER_TILE-2; i >= 0; i--) 
		pTile->m_pItem[i+1] = pTile->m_pItem[i];

	pTile->m_pItem[0] = pItem;
	//pTile->m_cTotalItem++;
	return TRUE;
}


class CItem * CMap::pGetItem(short sX, short sY, short * pRemainItemSprite, short * pRemainItemSpriteFrame, char * pRemainItemColor)
{
	class CTile * pTile;
	class CItem * pItem;
	register int i;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pItem =  pTile->m_pItem[0];
	if (pTile->m_cTotalItem == 0) return NULL;

	for (i = 0; i <= ITEMS_PER_TILE-2; i++)
		pTile->m_pItem[i] = pTile->m_pItem[i+1];
	pTile->m_cTotalItem--;
	pTile->m_pItem[pTile->m_cTotalItem] = NULL;

	if (pTile->m_pItem[0] == NULL) {
		*pRemainItemSprite      = 0;
		*pRemainItemSpriteFrame = 0;
		*pRemainItemColor       = 0;
	}
	else
	{
		*pRemainItemSprite      = pTile->m_pItem[0]->m_sSprite;
		*pRemainItemSpriteFrame = pTile->m_pItem[0]->m_sSpriteFrame;
		*pRemainItemColor       = pTile->m_pItem[0]->m_cItemColor;
	}

	return pItem;
}


int CMap::iCheckItem(short sX, short sY)
{
	class CTile * pTile;
	class CItem * pItem;

	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return NULL;

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);
	pItem =  pTile->m_pItem[0];
	if (pTile->m_cTotalItem == 0) return NULL;

	return pItem->m_sIDnum;
}


bool CMap::bIsValidLoc(short sX, short sY)
{
	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return FALSE;
	return TRUE;
}

bool CMap::bInit(char * pName)
{
	int i;
	ZeroMemory(m_cName, sizeof(m_cName));
	strcpy(m_cName, pName);

	ZeroMemory(m_cLocationName, sizeof(m_cLocationName));

	if (_bDecodeMapDataFileContents() == FALSE) 
		return FALSE;

	for (i = 0; i < MAXTELEPORTLOC; i++)
		m_pTeleportLoc[i] = NULL;

	return TRUE;
}

bool CMap::_bDecodeMapDataFileContents()
{
	HANDLE hFile;
	char  cMapFileName[64], cHeader[260];
	DWORD dwFileSize, nRead;
	register int i, ix, iy;
	char * token, cReadMode, *mapData, *tileData;
	char seps[] = "= \t\n"; 
	class CStrTok * pStrTok = NULL;
	class CTile * pTile;

	wsprintf(cMapFileName, "mapdata\\%s.amd",m_cName);

	hFile = CreateFile(cMapFileName, GENERIC_READ, NULL, NULL, OPEN_EXISTING, NULL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return FALSE;
	dwFileSize = GetFileSize(hFile, NULL);

	ZeroMemory(cHeader, sizeof(cHeader));
	ReadFile(hFile, (char *)cHeader, 256, &nRead, NULL);

	for (i = 0; i < 256; i++) 
	if (cHeader[i] == NULL) cHeader[i] = ' ';

	cReadMode = 0;

	pStrTok = new class CStrTok(cHeader, seps);
	token = pStrTok->pGet();
	//token = strtok( cHeader, seps );   
	while( token != NULL )   {

		if (cReadMode != 0) {
			switch (cReadMode) {
			case 1:
				m_sSizeX = atoi(token);
				cReadMode = 0;
				break;
			case 2:
				m_sSizeY = atoi(token);
				cReadMode = 0;
				break;
			case 3:
				m_sTileDataSize = atoi(token);
				cReadMode = 0;
				break;
			}
		}
		else {
			if (memcmp(token, "MAPSIZEX",8) == 0) cReadMode = 1;
			if (memcmp(token, "MAPSIZEY",8) == 0) cReadMode = 2;
			if (memcmp(token, "TILESIZE",8) == 0) cReadMode = 3; 
		}

		//token = strtok( NULL, seps );
		token = pStrTok->pGet();
	}

	m_pTile = (class CTile *)new class CTile[m_sSizeX * m_sSizeY];

	mapData = new char[dwFileSize];
	tileData = mapData;
	
	ReadFile(hFile, mapData, dwFileSize, &nRead, NULL);
	CloseHandle(hFile);

	for (iy = 0; iy < m_sSizeY; iy++)
		for (ix = 0; ix < m_sSizeX; ix++, tileData += m_sTileDataSize) {
			pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
			pTile->m_attribute = tileData[8];
			pTile->m_bIsMoveAllowed = (tileData[8] & 0x80) ? FALSE : TRUE;
			pTile->m_bIsTeleport = (tileData[8] & 0x40) ? TRUE : FALSE;
			pTile->m_bIsFarmingAllowed = (tileData[8] & 0x20) ? TRUE : FALSE;
			pTile->m_bIsWater = (*((short *)&tileData[0])== 19) ? TRUE : FALSE;
		}

	delete [] mapData;

	if (pStrTok != NULL) delete pStrTok;
	return TRUE;
}


bool CMap::bSearchTeleportDest(int sX, int sY, char * pMapName, int * pDx, int * pDy, char * pDir)
{
 register int i;

	for (i = 0; i < MAXTELEPORTLOC; i++)
	if ((m_pTeleportLoc[i] != NULL) && (m_pTeleportLoc[i]->m_sSrcX == sX) && (m_pTeleportLoc[i]->m_sSrcY == sY)) {

		memcpy(pMapName, m_pTeleportLoc[i]->m_cDestMapName, 10);
		*pDx  = m_pTeleportLoc[i]->m_sDestX;
		*pDy  = m_pTeleportLoc[i]->m_sDestY;
		*pDir = m_pTeleportLoc[i]->m_cDir;
		return TRUE;
	}

	return FALSE;
}

void CMap::SetDynamicObject(WORD wID, short sType, short sX, short sY, DWORD dwRegisterTime)
{
 class CTile * pTile;


	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	pTile->m_wDynamicObjectID   = wID;
	pTile->m_sDynamicObjectType = sType;
	pTile->m_dwDynamicObjectRegisterTime = dwRegisterTime;
}

bool CMap::bGetDynamicObject(short sX, short sY, short *pType, DWORD *pRegisterTime, int * pIndex)
{
 class CTile * pTile;


	if ((sX < 0) || (sX >= m_sSizeX) || (sY < 0) || (sY >= m_sSizeY)) return FALSE; 

	pTile = (class CTile *)(m_pTile + sX + sY*m_sSizeY);

	*pType = pTile->m_sDynamicObjectType;
	*pRegisterTime = pTile->m_dwDynamicObjectRegisterTime;
	if (pIndex != NULL) *pIndex = pTile->m_wDynamicObjectID;

	return TRUE;
}

int CMap::iGetEmptyNamingValue()
{
 register int i;

	for (i = 0; i < 1000; i++)
	if (m_bNamingValueUsingStatus[i] == FALSE) {

		m_bNamingValueUsingStatus[i] = TRUE;
		return i;
	}

	return -1;
}

void CMap::SetNamingValueEmpty(int iValue)
{
	m_bNamingValueUsingStatus[iValue] = FALSE;
}

bool CMap::bGetIsWater(short dX, short dY)
{
 class CTile * pTile;

	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);

	if (pTile->m_bIsWater == FALSE) return FALSE;

	return TRUE;
}



bool CMap::bGetIsFarm(short dX, short dY)
{
	class CTile * pTile;

	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);

	if (pTile->m_bIsFarmingAllowed == FALSE) return FALSE;

	return TRUE;
}

bool CMap::IsBuild(short dX, short dY)
{
	class CTile * pTile;

	if ((dX < 14) || (dX >= m_sSizeX - 16) || (dY < 12) || (dY >= m_sSizeY - 14)) return FALSE;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);

	return pTile->IsBuild();
}


int CMap::iAnalyze(char cType, int * pX, int * pY, int * pV1, int * pV2, int * pV3)
{
	switch (cType) {
	case 1:

		break;
	}

	return 0;
}

void CMap::SetTempMoveAllowedFlag(int dX, int dY, bool bFlag)
{
	class CTile * pTile;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	pTile->m_bIsTempMoveAllowed = bFlag;
}

int CMap::iRegisterOccupyFlag(int dX, int dY, int iSide, int iEKNum, int iDOI)
{
	int i;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return -1;

	for (i = 1; i < MAXOCCUPYFLAG; i++) 
	if (m_pOccupyFlag[i] == NULL) {

		m_pOccupyFlag[i] = new class COccupyFlag(dX, dY, iSide, iEKNum, iDOI);
		if (m_pOccupyFlag == NULL) return -1;
		else return i;
	}

	return -1;
}



void CMap::ClearSectorInfo()
{
 int ix, iy;

	for (ix = 0; ix < MAXSECTORS; ix++)
	for (iy = 0; iy < MAXSECTORS; iy++) {
		m_stSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stSectorInfo[ix][iy].iPlayerActivity  = 0;
	} 
}

void CMap::ClearTempSectorInfo()
{
 int ix, iy;

	for (ix = 0; ix < MAXSECTORS; ix++)
	for (iy = 0; iy < MAXSECTORS; iy++) {
		m_stTempSectorInfo[ix][iy].iNeutralActivity = 0;
		m_stTempSectorInfo[ix][iy].iAresdenActivity = 0;
		m_stTempSectorInfo[ix][iy].iElvineActivity  = 0;
		m_stTempSectorInfo[ix][iy].iMonsterActivity = 0;
		m_stTempSectorInfo[ix][iy].iPlayerActivity  = 0;
	} 
}

void CMap::_SetupNoAttackArea()
{
 int i, ix, iy;
 class CTile * pTile;

	for (i = 0; i < MAXNMR; i++) {
		if (m_rcNoAttackRect[i].top > 0) {

			for (ix = m_rcNoAttackRect[i].left; ix <= m_rcNoAttackRect[i].right; ix++)
			for (iy = m_rcNoAttackRect[i].top; iy <= m_rcNoAttackRect[i].bottom; iy++) {
				pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
				pTile->m_attribute |= 0x00000004;
			}
		}
		else if (m_rcNoAttackRect[i].top == -10) {
			for (ix = 0; ix < m_sSizeX; ix++)
			for (iy = 0; iy < m_sSizeY; iy++) {
				pTile = (class CTile *)(m_pTile + ix + iy*m_sSizeY);
				pTile->m_attribute |= 0x00000004;
			}
		}
	}
}

int CMap::iGetAttribute(int dX, int dY, int iBitMask)
{
 class CTile * pTile;

	if ((dX < 20) || (dX >= m_sSizeX - 20) || (dY < 20) || (dY >= m_sSizeY - 20)) return -1;

	pTile = (class CTile *)(m_pTile + dX + dY*m_sSizeY);
	return (pTile->m_attribute & iBitMask);
}

bool CMap::bAddCrusadeStructureInfo(char cType, short sX, short sY, char cSide)
{
	register int i;

	for (i = 0; i < MAXCRUSADESTRUCTURES; i++)
	if (m_stCrusadeStructureInfo[i].cType == NULL) {
		m_stCrusadeStructureInfo[i].cType = cType;
		m_stCrusadeStructureInfo[i].cSide = cSide;
		m_stCrusadeStructureInfo[i].sX = sX;
		m_stCrusadeStructureInfo[i].sY = sY;

		m_iTotalCrusadeStructures++;
		return TRUE;
	}

	return FALSE;
}

bool CMap::bRemoveCrusadeStructureInfo(short sX, short sY)
{
	register int i;

	for (i = 0; i < MAXCRUSADESTRUCTURES; i++)
	if ((m_stCrusadeStructureInfo[i].sX == sX) && (m_stCrusadeStructureInfo[i].sY == sY)) {
		m_stCrusadeStructureInfo[i].cType = NULL;
		m_stCrusadeStructureInfo[i].cSide = NULL;
		m_stCrusadeStructureInfo[i].sX = NULL;
		m_stCrusadeStructureInfo[i].sY = NULL;
		goto RCSI_REARRANGE;
	}

	return FALSE;

RCSI_REARRANGE:;

	for (i = 0; i < MAXCRUSADESTRUCTURES-1; i++)
	if ((m_stCrusadeStructureInfo[i].cType == NULL) && (m_stCrusadeStructureInfo[i+1].cType != NULL)) {
		m_stCrusadeStructureInfo[i].cType = m_stCrusadeStructureInfo[i+1].cType;
		m_stCrusadeStructureInfo[i].cSide = m_stCrusadeStructureInfo[i+1].cSide;
		m_stCrusadeStructureInfo[i].sX = m_stCrusadeStructureInfo[i+1].sX;
		m_stCrusadeStructureInfo[i].sY = m_stCrusadeStructureInfo[i+1].sY;

		m_stCrusadeStructureInfo[i+1].cType = NULL;
		m_stCrusadeStructureInfo[i+1].cSide = NULL;
		m_stCrusadeStructureInfo[i+1].sX = NULL;
		m_stCrusadeStructureInfo[i+1].sY = NULL;
	}

	m_iTotalCrusadeStructures--;
	return TRUE;
}



bool CMap::bAddCropsTotalSum()
{
	if(m_iTotalAgriculture < MAXAGRICULTURE)
	{
		m_iTotalAgriculture++;
		return TRUE;
	}
	return FALSE;
}


bool CMap::bRemoveCropsTotalSum()
{
	if(m_iTotalAgriculture < MAXAGRICULTURE)
	{
		m_iTotalAgriculture--;
		if(m_iTotalAgriculture < 0)
		{
			m_iTotalAgriculture = 0;
		}
		return TRUE;
	}
	return FALSE;
}

void CMap::RestoreStrikePoints()
{
	int i;

	for (i = 0; i < MAXSTRIKEPOINTS; i++) {
		m_stStrikePoint[i].iHP = m_stStrikePoint[i].iInitHP;
	}
}

void CMap::IncPlayerActivity(CClient * player)
{
	int iStX, iStY;

	iStX = player->m_sX / 20;
	iStY = player->m_sY / 20;
	m_stTempSectorInfo[iStX][iStY].iPlayerActivity++;

	switch (player->m_side) {
		case NEUTRAL: m_stTempSectorInfo[iStX][iStY].iNeutralActivity++; break;
		case ARESDEN: m_stTempSectorInfo[iStX][iStY].iAresdenActivity++; break;
		case ELVINE: m_stTempSectorInfo[iStX][iStY].iElvineActivity++;  break;
		case ISTRIA: m_stTempSectorInfo[iStX][iStY].iIstriaActivity++;  break;
	}
}