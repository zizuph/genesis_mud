/*
 * Goblin camp defines
 * TAPAKAH, 04/2005
 */

#ifndef _DAENBRAIGH_CAMP
#define _DAENBRAIGH_CAMP 1

#include "../daenbraigh.h"

#define C_OBJS (CAMPPATH + "objs/")
#define C_WEPS (CAMPPATH + "weps/")
#define C_ARMS (CAMPPATH + "arms/")
#define C_NPCS (CAMPPATH + "npcs/")
#define C_ROOM (CAMPPATH + "room/")

#define C_PRIVATE    (C_NPCS + "private")
#define C_CORPORAL   (C_NPCS + "corporal")
#define C_SERGEANT   (C_NPCS + "sergeant")
#define C_LIEUTENANT (C_NPCS + "lieutenant")
#define C_CAPTAIN    (C_NPCS + "captain")
#define C_GENERAL    (C_NPCS + "general")

#define C_CHAINMAIL  (C_ARMS + "chainmail")
#define C_HELMET     (C_ARMS + "helmet")
#define C_SHIELD     (C_ARMS + "shield")
#define C_CLOAK      (C_ARMS + "cloak")
#define C_OCHAINMAIL (C_ARMS + "ochainmail")
#define C_OHELMET    (C_ARMS + "ohelmet")
#define C_OSHIELD    (C_ARMS + "oshield")
#define C_OBRACERS   (C_ARMS + "obracers")
#define C_OGREAVES   (C_ARMS + "ogreaves")
#define C_OCLOAK     (C_ARMS + "ocloak")
#define C_GCHAINMAIL (C_ARMS + "gchainmail")
#define C_GCLOAK     (C_ARMS + "gcloak")

#define C_CLUB       (C_WEPS + "club")
#define C_OCLUB      (C_WEPS + "oclub")
#define C_GDAGGER    (C_WEPS + "gdagger")
#define C_GCLUB      (C_WEPS + "gclub")

#define C_OPAPER     (C_OBJS + "opaper")
#define C_GPAPER     (C_OBJS + "gpaper")
#define C_GMEDALLION (C_OBJS + "gmedallion")

#define C_ACLASS    (25)
#define C_WCLASS    (25)
#define C_OACLASS   (C_ACLASS + 10)
#define C_OWCLASS   (C_WCLASS + 10)
#define C_GACLASS   (C_ACLASS + 15)
#define C_GWCLASS   (C_WCLASS + 15)

#define GC_INSIDE   "_goblin_camp_inside"
#define GC_OUTSIDE  "_goblin_camp_outside"
#define GC_SOLDIER  "_goblin_camp_soldier"
#define GC_RANK     "_goblin_camp_rank"
#define GC_PROPERTY "_goblin_camp_property"

#define C_BASEMONEY 30
#define C_RANKMMULT  4

#define DAENBRAIGH_CAMP_PATH (C_ROOM + "path")
#endif

