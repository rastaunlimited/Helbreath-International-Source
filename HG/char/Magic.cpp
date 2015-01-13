// Magic.cpp: implementation of the CMagic class.
//
//////////////////////////////////////////////////////////////////////

#include "..\hg.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMagic::CMagic()
{
	ZeroMemory(m_cName, sizeof(m_cName));
	m_iAttribute = 0;
}

CMagic::~CMagic()
{										    

}

void CMagic::Effect_RecSP(Unit * caster, Unit * target, uint32 dthrow, uint32 droll, uint32 dbonus)
{
	int iSP, iMaxSP;	

	if(!target) return;

	iSP = dice(m_sValue[MAGICV_THROW], m_sValue[MAGICV_RANGE]) + m_sValue[MAGICV_BONUS];

	if(target->IsPlayer() && !target->m_bIsKilled)
	{
		CClient * player = (CClient*)target;

		iMaxSP = player->GetMaxSP();
		if (player->m_iSP < iMaxSP) {
			player->m_iSP += iSP;

			if (player->m_iSP > iMaxSP) 
				player->m_iSP = iMaxSP;

			player->Notify(NULL, NOTIFY_SP, NULL, NULL, NULL, NULL);
		}
	}
}