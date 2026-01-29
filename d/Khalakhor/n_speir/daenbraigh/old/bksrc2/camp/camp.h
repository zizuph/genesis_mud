/*
 * Goblin camp defines
 * TAPAKAH, 04/2005
 */

#ifndef _N_SPEIR_CAMP
#define _N_SPEIR_CAMP 1

#include "/w/tapakah/goblinvillage/src/nspeir.h"
#define COBJS CAMPPATH + "objs/"
#define CWEPS CAMPPATH + "weps/"
#define CARMS CAMPPATH + "arms/"
#define CNPCS CAMPPATH + "npcs/"
#define CROOM CAMPPATH

#define PRIVATE    CNPCS + "private"
#define CORPORAL   CNPCS + "corporal"
#define SERGEANT   CNPCS + "sergeant"
#define LIEUTENANT CNPCS + "liueutenant"
#define CAPTAIN    CNPCS + "captain"
#define GENERAL    CNPCS + "general"

#define CHAINMAIL CARMS + "chainmail"
#define HELMET    CARMS + "helmet"
#define SHIELD    CARMS + "shield"
#define CLOAK     CARMS + "cloak"
#define CLUB      CWEPS + "club"
#define ACLASS    25
#define WCLASS    25

#define OCHAINMAIL CARMS + "ochainmail"
#define OHELMET    CARMS + "ohelmet"
#define OSHIELD    CARMS + "oshield"
#define OBRACERS   CARMS + "obracers"
#define OGREAVES   CARMS + "ogreaves"
#define OCLOAK     CARMS + "ocloak"
#define OCLUB      CWEPS + "oclub"
#define OPAPER     COBJS + "opaper"
#define OACLASS    35
#define OWCLASS    35

#define GCHAINMAIL CARMS + "gchainmail"
#define GCLOAK     CARMS + "gcloak"
#define GDAGGER    CWEPS + "gdagger"
#define GCLUB      CWEPS + "gclub"
#define GPAPER     COBJS + "gpaper"
#define GMEDALLION COBJS + "gmedallion"
#define GACLASS    40
#define GWCLASS    40

#define GC_INSIDE   "_goblin_camp_inside"
#define GC_OUTSIDE  "_goblin_camp_outside"
#define GG_SOLDIER  "_goblin_garrison_soldier"
#define GG_RANK     "_goblin_garrison_rank"
#define GG_PROPERTY "_goblin_garrison_property"

#define BASEMONEY 30
#define RANKMMULT  4

#define BASEALIGN -400
#define ALIGNSHFT -100

#endif

