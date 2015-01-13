#ifndef _ITEM_H_
#define _ITEM_H_
#include <windows.h>
#include "..\..\defs.hpp"
#include "..\..\main.h"
//==============================================================================
class cItem
{
 public:	

	cItem();
	~cItem();
	void MakeItemInfo(char *pItemName, DWORD  dwItemCount, sWORD  wTouchEffectType, sWORD wTouchEffectValue1, sWORD wTouchEffectValue2, sWORD wTouchEffectValue3, sWORD wItemSpecEffectValue1, sWORD wItemSpecEffectValue2, sWORD wItemSpecEffectValue3, WORD wCurLifeSpan, DWORD dwAttribute, BYTE bItemColor, BOOL bPutItemInBank = TRUE, BOOL bIsItemEquipped = FALSE, sWORD wItemPosX = NULL, sWORD wItemPosY = NULL);
	
	char   ItemName[25];
	BYTE   ItemColor, DupItemCode;
	sWORD  TouchEffectType, TouchEffectValue1, TouchEffectValue2, TouchEffectValue3, ItemSpecEffectValue1,
			ItemSpecEffectValue2, ItemSpecEffectValue3, ItemPosX, ItemPosY;
	WORD   CurLifeSpan;
	DWORD  ItemCount, Attribute;
	uint64 ItemUniqueID;
	BOOL   IsItemEquipped, PutItemInBank;
};
//==============================================================================
#endif