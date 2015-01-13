// Map.h: interface for the CMap class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAP_H__12609160_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
#define AFX_MAP_H__12609160_8060_11D2_A8E6_00001C7030A6__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000

#include <windows.h>
#include <winbase.h>
#include "OccupyFlag.h"
#include "Tile.h"
#include "StrategicPoint.h"


// for Client Data
#define MAXTELEPORTLOC		200
#define MAXWAYPOINTCFG		200
#define MAXMGAR				50
#define MAXNMR				50
#define MAXSPOTMOBGENERATOR	100
#define MAXFISHPOINT		200
#define MAXMINERALPOINT		200
#define MAXOCCUPYFLAG		20001 //3001
#define MAXINITIALPOINT		20

#include "..\HG.h"
#include "..\StrTok.h"
#include "TeleportLoc.h"
#include "..\GlobalDef.h"

#define MAPTYPE_NORMAL				0
#define MAPTYPE_NOPENALTY_NOREWARD	1
#define MAXENERGYSPHERES			10

#define MAXSTRATEGICPOINTS			200
#define MAXSECTORS					60
#define MAXSTRIKEPOINTS				20

#define MAXITEMEVENTS				50

#define MAXHELDENIANDOOR	10 
#define MAXDYNAMICGATES		10
#define MAXHELDENIANTOWER	200

class CMap  
{
public:

	void RestoreStrikePoints();
	bool bRemoveCrusadeStructureInfo(short sX, short sY);
	bool bAddCrusadeStructureInfo(char cType, short sX, short sY, char cSide);
	int iGetAttribute(int dX, int dY, int iBitMask);
	void _SetupNoAttackArea();
	void ClearTempSectorInfo();
	void ClearSectorInfo();
	int iRegisterOccupyFlag(int dX, int dY, int iSide, int iEKNum, int iDOI);
	int  iCheckItem(short sX, short sY);
	void SetTempMoveAllowedFlag(int dX, int dY, bool bFlag);
	int iAnalyze(char cType, int *pX, int *pY, int * pV1, int *pV2, int * pV3);
	bool bGetIsWater(short dX, short dY);
	bool bGetIsFarm(short dX, short dY);
	bool IsBuild(short dX, short dY);
	bool bAddCropsTotalSum();
	bool bRemoveCropsTotalSum();
	bool bGetIsMoveAllowedTile(short dX, short dY);
	bool bGetIsMoveAllowedTile(Point p);
	void SetNamingValueEmpty(int iValue);
	int iGetEmptyNamingValue();
	bool bGetDynamicObject(short sX, short sY, short * pType, DWORD * pRegisterTime, int * pIndex = NULL);
	void SetDynamicObject(WORD wID, short sType, short sX, short sY, DWORD dwRegisterTime);
	bool bGetIsTeleport(short dX, short dY);
	bool bSearchTeleportDest(int sX, int sY, char * pMapName, int * pDx, int * pDy, char * pDir);
	bool bInit(char * pName);
	bool bIsValidLoc(short sX, short sY);
	class CItem * pGetItem(short sX, short sY, short * pRemainItemSprite, short * pRemainItemSpriteFrame, char * pRemainItemColor);
	bool bSetItem(short sX, short sY, class CItem * pItem);
	void ClearDeadOwner(short sX, short sY);
	void ClearOwner(/*int iDebugCode,*/ short sOwnerH, char cOwnerType, short sX, short sY);
	bool bGetMoveable(short dX, short dY, short * pDOtype = NULL, class CItem * pTopItem = NULL); 
	void GetOwner(short * pOwner, char * pOwnerClass, short sX, short sY);
	void SetOwner(short sOwner, char cOwnerClass, short sX, short sY);
	void GetDeadOwner(short * pOwner, char * pOwnerClass, short sX, short sY);
	void SetDeadOwner(short sOwner, char cOwnerClass, short sX, short sY);
	Unit * GetOwner(short sX, short sY);
	Unit * GetDeadOwner(short sX, short sY);
	void IncPlayerActivity(CClient * player);

	CMap(class CGame * pGame);
	virtual ~CMap();

	class CTile * m_pTile;
	class CGame * m_pGame;
	char  m_cName[11];
	char  m_cLocationName[11];
	short m_sSizeX, m_sSizeY, m_sTileDataSize;
	class CTeleportLoc * m_pTeleportLoc[MAXTELEPORTLOC];

	//short m_sInitialPointX, m_sInitialPointY;
	POINT m_pInitialPoint[MAXINITIALPOINT];

	bool m_bIsApocalypseMap;
	int	  m_iApocalypseMobGenType, m_iApocalypseBossMobNpcID;
	RECT	m_sApocalypseBossMobRect;

	char  m_cDynamicGateType;
	short m_sDynamicGateCoordRectX1, m_sDynamicGateCoordRectY1, m_sDynamicGateCoordRectX2, m_sDynamicGateCoordRectY2;
	char  m_cDynamicGateCoordDestMap[11];
	short m_sDynamicGateCoordTgtX, m_sDynamicGateCoordTgtY;

	char  m_cHeldenianModeMap;
	bool m_bIsHeldenianMap;
	short m_sHeldenianWinningZoneX;
	short m_sHeldenianWinningZoneY;
	
	struct {
		char  cDir;
		short dX;
		short dY;
	} m_stHeldenianGateDoor[MAXHELDENIANDOOR];

	struct {
		short sTypeID;
		short dX;
		short dY;
		char  cSide;
	} m_stHeldenianTower[MAXHELDENIANTOWER];

	bool  m_bNamingValueUsingStatus[1000]; // 0~999
	bool  m_bRandomMobGenerator;
	char  m_cRandomMobGeneratorLevel;
	int   m_iTotalActiveObject;
	int   m_iTotalAliveObject;
	int   m_iMaximumObject;

	char  m_cType;
	bool  m_bIsFixedDayMode;		
	bool  m_bIsFixedSnowMode;
	struct {		    
		bool bDefined;
		char cType;				// 1:RANDOMAREA   2:RANDOMWAYPOINT

		char cWaypoint[10];     
		RECT rcRect;

		int  iTotalActiveMob;
		int  iMobType;
		int  iMaxMobs;
		int  iCurMobs;

	} m_stSpotMobGenerator[MAXSPOTMOBGENERATOR];

	POINT m_WaypointList[MAXWAYPOINTCFG];
	RECT  m_rcMobGenAvoidRect[MAXMGAR];
	RECT  m_rcNoAttackRect[MAXNMR];

	POINT m_FishPointList[MAXFISHPOINT];
	int   m_iTotalFishPoint, m_iMaxFish, m_iCurFish;

	bool  m_bMineralGenerator;
	char  m_cMineralGeneratorLevel;
	POINT m_MineralPointList[MAXMINERALPOINT];
	int   m_iTotalMineralPoint, m_iMaxMineral, m_iCurMineral;

	char  m_cWhetherStatus;			
	DWORD m_dwWhetherLastTime, m_dwWhetherStartTime;  

	int   m_iLevelLimit;
	int   m_iUpperLevelLimit;

	class COccupyFlag * m_pOccupyFlag[MAXOCCUPYFLAG];
	int   m_iTotalOccupyFlags;

	class CStrategicPoint * m_pStrategicPointList[MAXSTRATEGICPOINTS];
	
	bool	m_bIsAttackEnabled;
	bool	m_isPartyDisabled;
	bool	m_isShieldDisabled;
	bool	m_isArmorDisabled;
	bool	m_isChatDisabled;
	bool	m_magicLimited[MAXMAGICTYPE];
	bool	m_isPermIllusionOn;

	bool  m_bIsFightZone;

	struct {
		char cType;
		int sX, sY;

	} m_stEnergySphereCreationList[MAXENERGYSPHERES];

	int m_iTotalEnergySphereCreationPoint;

	struct {
		char cResult;
		int aresdenX, aresdenY, elvineX, elvineY;
	} m_stEnergySphereGoalList[MAXENERGYSPHERES];

	int m_iTotalEnergySphereGoalPoint;

	bool m_bIsEnergySphereGoalEnabled;
	int m_iCurEnergySphereGoalPointIndex; 

		struct {
		int iPlayerActivity;
		int iNeutralActivity;
		int iAresdenActivity;
		int iElvineActivity;
		int iIstriaActivity;
		int iMonsterActivity;

	} m_stSectorInfo[MAXSECTORS][MAXSECTORS], m_stTempSectorInfo[MAXSECTORS][MAXSECTORS];

	int m_iMaxNx, m_iMaxNy, m_iMaxAx, m_iMaxAy, m_iMaxEx, m_iMaxEy, m_iMaxMx, m_iMaxMy, m_iMaxPx, m_iMaxPy;

	struct {
		char cRelatedMapName[11];
		int iMapIndex;
		int dX, dY;
		int iHP, iInitHP;

		int iEffectX[5];
		int iEffectY[5];

	} m_stStrikePoint[MAXSTRIKEPOINTS];
	int m_iTotalStrikePoints;

	bool m_bIsDisabled;

	struct {
		char cType;					
		char cSide;
		short sX, sY;			
	} m_stCrusadeStructureInfo[MAXCRUSADESTRUCTURES];
	int m_iTotalCrusadeStructures;
	int m_iTotalAgriculture;  

	struct {
		char cItemName[21];
		int iAmount;
		int iTotalNum;				
		int iMonth;
		int iDay;
		int iType;
		char *cMob[5];

		int iCurNum;
		int	iNumMob;
	} m_stItemEventList[MAXITEMEVENTS];
	int m_iTotalItemEvents;

	bool m_bIsEnergySphereAutoCreation;

	short sMobEventAmount ;         


private:
	bool _bDecodeMapDataFileContents();
};

#endif // !defined(AFX_MAP_H__12609160_8060_11D2_A8E6_00001C7030A6__INCLUDED_)
