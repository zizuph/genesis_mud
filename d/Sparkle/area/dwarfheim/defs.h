#include "../../sys/defs.h"

#define S_AREA_DIR		(S_DOMAIN_AREA_DIR + "dwarfheim/")

#define S_AREA_ARM_DIR		(S_AREA_DIR + "arm/")
#define S_AREA_NPC_DIR		(S_AREA_DIR + "npc/")
#define S_AREA_OBJ_DIR		(S_AREA_DIR + "obj/")
#define S_AREA_VAR_DIR		(S_AREA_DIR + "var/")
#define S_AREA_WEP_DIR		(S_AREA_DIR + "wep/")
#define S_AREA_ROOM_DIR		(S_AREA_DIR + "room/")

#define S_AREA_FORT             "fort/"
#define S_AREA_WILD             "wild/"

//--------------------------------------------------------------------------

// This part contains definitions that legacy code from Dwarfheim
// relies on. Using the definitions elsewhere is discouraged.

#include <stdproperties.h>

#define NF(message)	notify_fail(message)
#define ETP		environment(this_player())
#define ETO		environment(this_object())
#define BS(message)	break_string(message, 75)
#define E(x)            environment(x)

#define I add_prop(ROOM_I_INSIDE,1)

#define D_DIR		"/d/Genesis/start/dwarf/"
#define D_OBJ		D_DIR + "obj/"
#define D_MON		D_DIR + "monster/"
#define D_L1		D_DIR + "level_1/"
#define D_L2		D_DIR + "level_2/"

#define LVL3            D_DIR +"lvl3/"
#define LVL1            D_DIR +"lvl1/"
#define LVL2            D_DIR +"lvl2/"

#define ANTHANDLER (D_MON+"anthandler.c")

/* a property for the ants */

#define ANTSCENT  "_an_ant_walked_from_"
