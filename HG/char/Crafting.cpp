#include "Crafting.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCrafting::CCrafting()
{
 int i;
	
	ZeroMemory(m_cName, sizeof(m_cName));
	m_iSkillLimit = 0;
	m_iDifficulty = 0;

	for (i = 0; i < 12; i++)
		m_sArray[i] = -1;
}

CCrafting::~CCrafting()
{

}