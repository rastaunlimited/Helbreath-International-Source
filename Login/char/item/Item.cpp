#include "Item.h"
//==============================================================================
cItem::cItem()
{
	ZeroMemory(ItemName, sizeof(ItemName));
	ItemColor = DupItemCode = 0;
	TouchEffectType = TouchEffectValue1 = TouchEffectValue2 = TouchEffectValue3 = ItemSpecEffectValue1 =
	ItemSpecEffectValue2 = ItemSpecEffectValue3 = ItemPosX = ItemPosY =0;
	CurLifeSpan = 0;
	ItemCount = Attribute = 0;
	ItemUniqueID = 0;
	IsItemEquipped = PutItemInBank = FALSE;
}
//==============================================================================
cItem::~cItem()
{
}
//==============================================================================
void cItem::MakeItemInfo(char *pItemName, DWORD  dwItemCount, sWORD  wTouchEffectType, sWORD wTouchEffectValue1, sWORD wTouchEffectValue2, sWORD wTouchEffectValue3, sWORD wItemSpecEffectValue1, sWORD wItemSpecEffectValue2, sWORD wItemSpecEffectValue3, WORD wCurLifeSpan, DWORD dwAttribute, BYTE bItemColor, BOOL bPutItemInBank, BOOL bIsItemEquipped, sWORD wItemPosX, sWORD wItemPosY)
{
	ZeroMemory(ItemName, sizeof(ItemName));
	SafeCopy(ItemName, pItemName);
	ItemCount = dwItemCount;
	TouchEffectType = wTouchEffectType;
	TouchEffectValue1 = wTouchEffectValue1;
	TouchEffectValue2 = wTouchEffectValue2;
	TouchEffectValue3 = wTouchEffectValue3;
	ItemSpecEffectValue1 = wItemSpecEffectValue1;
	ItemSpecEffectValue2 = wItemSpecEffectValue2;
	ItemSpecEffectValue3 = wItemSpecEffectValue3;
	CurLifeSpan = wCurLifeSpan;
	Attribute = dwAttribute;
	ItemColor = bItemColor;
	IsItemEquipped = bIsItemEquipped;
	PutItemInBank = bPutItemInBank;
	ItemPosX = wItemPosX;
	ItemPosY = wItemPosY;
}
//==============================================================================