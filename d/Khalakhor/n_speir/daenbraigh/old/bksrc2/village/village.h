/*
 * Include file for village rooms
 * TAPAKAH, 04/2005
 */

#ifndef _N_SPEIR_VILLAGE
#define _N_SPEIR_VILLAGE 1

#include "../nspeir.h"

#define GV_OUTSIDE "_goblin_village_outside"
#define GV_VILLAGER "_goblin_village_inhabitant"

#define VOBJS VILLAGEPATH + "objs/"
#define VNPCS VILLAGEPATH + "npcs/"
#define VWEPS VILLAGEPATH + "weps/"
#define VARMS VILLAGEPATH + "arms/"
#define VROOM VILLAGEPATH + "room/"
#define VTEXT VILLAGEPATH + "text/"
#define VMAGI VILLAGEPATH + "magi/"

#define VOBJID   "_goblin_village"

#define GARBAGE  VOBJS + "garbage"
#define CART     VOBJS + "cart"
#define CHEST    VOBJS + "chest"
#define SCROLL   VOBJS + "scroll"
#define SKULL    VOBJS + "skull"
#define SCEPTRE  VOBJS + "sceptre"
#define TENT     VOBJS + "tent"

#define SHIRT    VARMS + "shirt"
#define BREECHES VARMS + "breeches"
#define ROBE     VARMS + "robe"
#define SMMAIL   VARMS + "mail";
#define SMBOOTS  VARMS + "boots";

#define KNIFE    VWEPS + "knife"
#define CLUB     VWEPS + "club"
#define SMHAMMER VARMS + "hammer";

#define VWCLASS  20
#define VACLASS  15
#define VRCLASS  35
#define VCCLASS  30

#define VILLAGER VNPCS + "villager"
#define ELDER    VNPCS + "elder"
#define BARMAN   VNPCS + "barman"
#define SMITH    VNPCS + "smith"
#define SHPKPR   VNPCS + "shopkeeper"
#define ESERVANT VNPCS + "elderservant"

#define SCROLL_TEXT VTEXT + "scroll"

#define SCEPTRE_MOD 0.2

#define VILLAGENAME "Daenbraigh"

#define VILLAGERADJ ({"dirty","sweaty","sunken","ugly","long-armed","sad","tired"})
#define VILLAGERINV ({SHIRT,BREECHES,KNIFE})
#define VILLAGERFIN 50
#define VILLAGERALIGN -200

#endif
