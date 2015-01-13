#ifndef LGNSVCS_H
#define LGNSVCS_H
#include "NetMessages.h"

const enum lgnSvcsCmds{
	CMD_LGNSVC_MAGEHAT,
	CMD_LGNSVC_BMAGEHAT,
	CMD_LGNSVC_WARRIORHELM,
	CMD_LGNSVC_BMAGEHELM,
	CMD_LGNSVC_TOARE,
	CMD_LGNSVC_TOELV,
	//CMD_LGNSVC_TOIST,
	CMD_LGNSVC_MAJ2,
	CMD_LGNSVC_MAJ20,
	CMD_LGNSVC_GOLD10,
	CMD_LGNSVC_GOLD100,
	CMD_LGNSVC_REP10,
	CMD_LGNSVC_REP100
};

const struct lgnPtsSvc{
	char * desc;
	char * name;
	unsigned long price;
	unsigned short cmd;
} lgnPtsSvcs[] = {
	{"MP7 Indestructible Golden Wizard Hat", "LegionHat MP7", 25, CMD_LGNSVC_MAGEHAT},
	{"HP7 Indestructible Golden Wizard Hat", "LegionHat HP7", 25, CMD_LGNSVC_BMAGEHAT},
	{"HP7 Indestructible Golden Winged Helm", "LegionHelm HP7", 25, CMD_LGNSVC_WARRIORHELM},
	{"MP7 Indestructible Golden Winged Helm", "LegionHelm MP7", 25, CMD_LGNSVC_BMAGEHELM},
	{"Town Change (Aresden)", "TC(Are)", 10, CMD_LGNSVC_TOARE},
	{"Town Change (Elvine)", "TC(Elv)", 10, CMD_LGNSVC_TOELV},
	//{"Town Change (Istria)", "TC(Ist)", 10, CMD_LGNSVC_TOIST},
	{"2 Majestic points", "2 Maj", 1, CMD_LGNSVC_MAJ2},
	{"20 Majestic points", "20 Maj", 10, CMD_LGNSVC_MAJ20},
	{"10,000 Gold", "10k Gold", 1, CMD_LGNSVC_GOLD10},
	{"100,000 Gold", "100k Gold", 10, CMD_LGNSVC_GOLD100},
	{"10 Reputations points", "10 Rep", 1, CMD_LGNSVC_REP10},
	{"100 Reputations points", "100 Rep", 10, CMD_LGNSVC_REP100},
	{"","",0,0}
};

#endif // LGNSVCS_H
