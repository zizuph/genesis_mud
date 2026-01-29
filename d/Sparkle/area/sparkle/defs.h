#include "../../sys/defs.h"

#define S_AREA_DIR		(S_DOMAIN_AREA_DIR + "sparkle/")

#define S_AREA_ARM_DIR		(S_AREA_DIR + "arm/")
#define S_AREA_NPC_DIR		(S_AREA_DIR + "npc/")
#define S_AREA_OBJ_DIR		(S_AREA_DIR + "obj/")
#define S_AREA_VAR_DIR		(S_AREA_DIR + "var/")
#define S_AREA_WEP_DIR		(S_AREA_DIR + "wep/")
#define S_AREA_ROOM_DIR		(S_AREA_DIR + "room/")

#define S_AREA_FORT             "fort/"
#define S_AREA_SHIP             "ship/"
#define S_AREA_TOWN             "town/"
#define S_AREA_WILD             "wild/"
#define S_AREA_TOWER            "tower/"

//--------------------------------------------------------------------------

// This part contains definitions that legacy code from Sparkle
// relies on. Using the definitions elsewhere is discouraged.

#define ENV(x)		environment (x)
#define CAP(x)		capitalize (x)
#define LOW(x)		lower_case (x)

#define NF(x)		notify_fail (x)
#define NFN(x)		notify_fail ((x) + "\n")

#define WRITE(x)	this_player ()->catch_tell (x)

#define HE(x)		(x)->query_pronoun ()
#define HIM(x)		(x)->query_objective ()
#define HIS(x)		(x)->query_possessive ()

