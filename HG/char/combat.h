#define HITRATIOFACTOR		80.0f
#define MAXSKILLPOINTS		900

bool CheckResistingMagicSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio);
bool checkResistingPoisonSuccess(short sOwnerH, char cOwnerType);
bool checkResistingIceSuccess(char cAttackerDir, short sTargetH, char cTargetType, int iHitRatio);
void CalculateSSN_SkillIndex(int iClientH, short sSkillIndex, int iValue);
void CalculateSSN_ItemIndex(int iClientH, short sWeaponIndex, int iValue);
int calculateAttackEffect(short sTargetH, char cTargetType, short sAttackerH, char cAttackerType, int tdX, int tdY, int iAttackMode, bool bNearAttack = false, bool bIsDash = false);
void EnduStrippingDamage(short sTargetH, short sAttackerH, char cAttackerType, int item, int higherStripEndu);
