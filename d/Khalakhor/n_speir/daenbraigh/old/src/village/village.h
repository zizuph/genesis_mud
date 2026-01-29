/*
 * Include file for village rooms
 * TAPAKAH, 06/2006
 */

#ifndef _DAENBRAIGH_VILLAGE
#define _DAENBRAIGH_VILLAGE 1

#include "../daenbraigh.h"

#define VILLAGE_NAME "Daenbraigh"

#define V_OUTSIDE "_goblin_village_outside"
#define V_VILLAGER "_goblin_village_inhabitant"

#define V_OBJS (VILLAGEPATH + "objs/")
#define V_NPCS (VILLAGEPATH + "npcs/")
#define V_WEPS (VILLAGEPATH + "weps/")
#define V_ARMS (VILLAGEPATH + "arms/")
#define V_ROOM (VILLAGEPATH + "room/")
#define V_TEXT (VILLAGEPATH + "text/")
#define V_MAGI (VILLAGEPATH + "magi/")

#define V_ROAD_BASE  (V_ROOM + "road")
#define V_HUT_BASE   (V_ROOM + "hut")
#define V_TOWER_BASE (V_ROOM + "tower")

#define V_GOBLIN    (V_NPCS + "villager")
#define V_ELDER     (V_NPCS + "elder")
#define V_BARMAN    (V_NPCS + "barman")
#define V_SMITH     (V_NPCS + "smith")
#define V_SHPKPR    (V_NPCS + "shopkeeper")
#define V_SERVANT   (V_NPCS + "servant")
#define V_COURIER   (V_NPCS + "courier")

#define V_OBJID   "_goblin_village"

#define V_GARBAGE  (V_OBJS + "garbage")
#define V_CART     (V_OBJS + "cart")
#define V_CHEST    (V_OBJS + "chest")
#define V_SCROLL   (V_OBJS + "scroll")
#define V_SKULL    (V_OBJS + "skull")
#define V_SCEPTRE  (V_OBJS + "sceptre")
#define V_TOOTH    (V_OBJS + "tooth")
#define V_KEY      (V_OBJS + "bonekey")
#define V_LETTER   (V_OBJS + "letter")

#define V_SHIRT    (V_ARMS + "shirt")
#define V_BREECHES (V_ARMS + "breeches")
#define V_ROBE     (V_ARMS + "robe")
#define V_BOOTS    (V_ARMS + "boots")
#define V_MAIL     (V_ARMS + "mail")

#define V_KNIFE    (V_WEPS + "knife")
#define V_HAMMER   (V_WEPS + "hammer")

#define V_MAGI_COLD    (V_MAGI + "cold")
#define V_MAGI_CONFUSE (V_MAGI + "confuse")

#define V_SCROLL_TEXT  (V_TEXT + "scroll")

#define V_IS_ASLEEP    ("_v_is_asleep")
#define V_COURIER_REPORTED ("_v_courier_reported")
#define V_WCLASS  20
#define V_ACLASS  15

#define V_KEY_VALUE 11102215

#define V_GOBLIN_ADJ ({"dirty","sweaty","sunken","ugly","long-armed","sad","tired"})
#define V_GOBLIN_INV ({V_SHIRT,V_BREECHES,V_KNIFE})
#define V_GOBLIN_MON 50
#define V_GOBLIN_ALG 0

#endif
