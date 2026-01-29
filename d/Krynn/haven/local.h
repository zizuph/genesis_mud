#include "/d/Krynn/common/defs.h"

#define PARENT  "/d/Krynn/haven/"
#define STD     PARENT + "std/"
#define HDIR    PARENT + "town/"
#define HOBJ    HDIR + "obj/"
#define HROOM   HDIR + "room/"
#define HNPC    HDIR + "npc/"
#define HARM    HDIR + "arm/"
#define HWEP    HDIR + "wep/"
#define HFOOD   HDIR + "food/"
#define DDIR    PARENT + "dwarf_camp/"
#define DSTD    DDIR + "std/"
#define DOBJ    DDIR + "obj/"
#define DNPC    DDIR + "npc/"
#define DWEP    DDIR + "wep/"
#define DARM    DDIR + "arm/"
#define DLOG    DDIR + "log/"
#define DROOM   DDIR + "room/"
#define RDIR    PARENT + "road/"
#define KSTD    PARENT + "std/"

/* inherit files */
#define MOUNTBASE    STD + "mountain_base"
#define CAMPBASE     STD + "camp_base"
#define ROADBASE     STD + "road_base"
#define FORESTBASE   STD + "forest_base"
#define IN           STD + "inside_base"
#define OUT          STD + "outside_base"
#define HAVENBASE    STD + "haven_base"
#define HAVENINBASE  STD + "haven_in_base"

#define SEEKERBASE   STD + "seeker_base"

/* places to visit */
#define DEFAULT      0
#define ROAD         1
#define TOWN         2
#define VILLAGE      2
#define DWARVES      3
#define MOUNTAINS    4
#define FOREST       5

/* Connections to the outside world */
#define WAYRETH  "/d/Krynn/wayreth/forest/"

#define RESPONSIBLE ({"tibbit"})

/* Quest bits */
/* Tibbit, 11 March 1998 */
#define SEEKER_CHALICE_QUEST_GROUP 1
#define SEEKER_CHALICE_QUEST_BIT   17
#define SEEKER_CHALICE_QUEST_EXP   60


