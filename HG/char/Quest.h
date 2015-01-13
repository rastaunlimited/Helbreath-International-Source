// Quest.h: interface for the CQuest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
#define AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#define QUESTTYPE_MONSTERHUNT				1
#define QUESTTYPE_MONSTERHUNT_TIMELIMIT		2
#define QUESTTYPE_ASSASSINATION 			3
#define QUESTTYPE_DELIVERY					4
#define QUESTTYPE_ESCORT					5
#define QUESTTYPE_GUARD						6
#define QUESTTYPE_GOPLACE					7
#define QUESTTYPE_BUILDSTRUCTURE			8
#define QUESTTYPE_SUPPLYBUILDSTRUCTURE		9
#define QUESTTYPE_STRATEGICSTRIKE			10
#define QUESTTYPE_SENDTOBATTLE				11
#define QUESTTYPE_SETOCCUPYFLAG				12
class CQuest  
{
public:

	char m_side;

	int m_iType;
	int m_iTargetType;
	int m_iMaxCount;

	int m_iFrom;

	int m_iMinLevel;
	int m_iMaxLevel;

	int m_iRequiredSkillNum;
	int m_iRequiredSkillLevel;

	int m_iTimeLimit; 				
	int m_iAssignType;


	int m_iRewardType[4]; 
	int m_iRewardAmount[4];

	int m_iContribution;
	int m_iContributionLimit;

	int m_iResponseMode;
	char m_cTargetName[21];
	int  m_sX, m_sY, m_iRange;

	int  m_iQuestID;

	int  m_iReqContribution;


	CQuest();
	virtual ~CQuest();

};

#endif // !defined(AFX_QUEST_H__3E61C780_FF48_11D3_9DC2_00A0CC5B45EE__INCLUDED_)
