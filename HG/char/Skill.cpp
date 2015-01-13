// Skill.cpp: implementation of the CSkill class.
//
//////////////////////////////////////////////////////////////////////

#include "Skill.h"
#include "..\math.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSkill::CSkill()
{
	ZeroMemory(m_cName, sizeof(m_cName));
}

CSkill::~CSkill()
{ 

}										    


int SKILLCROPSTABLE[9][9] = 
// 20  30  40  50  60  70  80  90 100
{
	42, 34, 27, 21, 16, 12,  9,  7,  6,  //20
	43, 40, 33, 27, 22, 18, 15, 13, 10,	//30
	44, 41, 38, 32, 27, 23, 20, 18, 13,  //40
	45, 42, 39, 36, 31, 27, 24, 22, 15,  //50
	46, 43, 40, 37, 34, 30, 27, 25, 16,  //60
	47, 44, 41, 38, 35, 32, 29, 27, 20,  //70
	48, 45, 42, 39, 36, 33, 30, 28, 23,  //80
	49, 46, 43, 40, 37, 34, 31, 28, 25,  //90
	50, 47, 44, 41, 38, 35, 32, 29, 26  //100
};

int CROPSDROPTABLE[9][9] = 
// 20  30  40  50  60  70  80  90 100
{
	40,  0,  0,  0,  0,  0,  0,  0,  0,  //20
	41, 38,  0,  0,  0,  0,  0,  0,  0,	//30
	43, 40, 36,  0,  0,  0,  0,  0,  0,  //40
	46, 42, 38, 35,  0,  0,  0,  0,  0,  //50
	50, 45, 41, 37, 33,  0,  0,  0,  0,  //60
	55, 49, 44, 40, 35, 31,  0,  0,  0,  //70
	61, 54, 48, 43, 38, 33, 30,  0,  0,  //80
	68, 60, 53, 47, 42, 37, 32, 28,  0,  //90
	76, 67, 59, 52, 46, 41, 35, 29, 24  //100
};

int probabilityTable(int x,int y,int iTable) 
{
	int iProb;
	int iX,iY;

	iX = (x - 20) / 10;
	iY = (y - 20) / 10;

	if( iX < 0 || iX > 8) return 0;
	if( iY < 0 || iY > 8) return 0;

	iProb = dice(1,100);

	if(iTable == 1){
		if( SKILLCROPSTABLE[iX][iY] >= iProb )
			return SKILLCROPSTABLE[iX][iY];
		else
			return 0;
	}
	else if(iTable == 2){
		if( CROPSDROPTABLE[iX][iY] >= iProb )
			return CROPSDROPTABLE[iX][iY];
		else
			return 0;
	}
	else return 0;
}