#ifndef DRAGONARMY_DEFS
#define DRAGONARMY_DEFS

#include "/d/Ansalon/common/defs.h"

#define DA_TESTING 0
#if DA_TESTING
#define DBGMSG(x)   find_player("*guildmaster*")->catch_msg(x)
#else
#define DBGMSG(x)
#endif DA_TESTING

#define DRAGONARMY_DIR		"/d/Ansalon/guild/dragonarmy/"
#define DRAGONARMY_LIB		(DRAGONARMY_DIR + "lib/")
#define DRAGONARMY_HELP		(DRAGONARMY_DIR + "help/")
#define DRAGONARMY_LOG		(DRAGONARMY_DIR + "log/")
#define DRAGONARMY_OBJ		(DRAGONARMY_DIR + "obj/")
#define DRAGONARMY_ROOM		(DRAGONARMY_DIR + "room/")
#define DRAGONARMY_SOUL		(DRAGONARMY_DIR + "soul/")
#define DRAGONARMY_SH		(DRAGONARMY_DIR + "shadow/")
#define DRAGONARMY_DRAGON	(DRAGONARMY_DIR + "dragons/")
#define DRAGONARMY_NPC		(DRAGONARMY_DIR + "npc/")
#define DRAGONARMY_SPECIALS (DRAGONARMY_DIR + "specials/")
#define DRAGONARMY_DATA     (DRAGONARMY_DIR + "data/")
#define RDA_WOUNDS_PROP "_rda_wounds_prop_setting_"

#define MANAGER (DRAGONARMY_OBJ + "manager")
#define DRAGON_MANAGER (DRAGONARMY_DRAGON + "dragon_manager")
#define TEMP_DRAGON_ROOM (DRAGONARMY_DRAGON + "tmp")
#define DRAGONARMY_BLUE_STARTLOC DRAGONARMY_ROOM + "start_blue"
#define DRAGONARMY_RED_STARTLOC DRAGONARMY_ROOM + "start_red"
#define ROOM_M_DA_DRAGONSTEED_NO_LAND "_room_m_da_dragonsteed_no_land"

#define DRAGONARMY_OCC_EMBLEM (DRAGONARMY_OBJ + "horn")

#define DRAGONARMY_BASE_SOUL (DRAGONARMY_SOUL + "dragonarmy_soul")
#define DRAGONARMY_RED_SOUL (DRAGONARMY_SOUL + "dragonarmy_red_soul")
#define DRAGONARMY_BLUE_SOUL (DRAGONARMY_SOUL + "dragonarmy_blue_soul")
#define DRAGONARMY_GREEN_SOUL (DRAGONARMY_SOUL + "dragonarmy_green_soul")
#define DRAGONARMY_BLACK_SOUL (DRAGONARMY_SOUL + "dragonarmy_black_soul")
#define DRAGONARMY_WHITE_SOUL (DRAGONARMY_SOUL + "dragonarmy_white_soul")

#define DRAGONARMY_BASE_SH	(DRAGONARMY_SH + "dragonarmy_sh")
#define RED_SHADOW		(DRAGONARMY_SH + "dragonarmy_red_sh")
#define BLUE_SHADOW		(DRAGONARMY_SH + "dragonarmy_blue_sh")
#define GREEN_SHADOW		(DRAGONARMY_SH + "dragonarmy_green_sh")
#define BLACK_SHADOW		(DRAGONARMY_SH + "dragonarmy_black_sh")
#define WHITE_SHADOW		(DRAGONARMY_SH + "dragonarmy_white_sh")

#define GUILD_STYLE   "fighter"
#define GUILD_NAME    "Dragonarmy"

#define BIT(x) (1 << x)

#define PUN_NOTRAIN	BIT(0)
#define PUN_NOGUILDXP	BIT(1)
#define PUN_DEATH	BIT(2)
#define PUN_NOARMOURY	BIT(3)
#define PUN_NOBOARD	BIT(4)
#define PUN_NOFUND_TQ	BIT(5)
#define PUN_NOFUND_H	BIT(6)
#define PUN_NOFUND_O	BIT(7)
#define PUN_NOGURU	BIT(8)
#define PUN_NOWHO BIT(9)

#define IS_MEMBER(ob)     (ob->query_dragonarmy_occ_member())

#define WHITE_ARMY "white"
#define BLACK_ARMY "black"
#define RED_ARMY   "red"
#define GREEN_ARMY "green"
#define BLUE_ARMY  "blue"

#define DA_COLORS ({"white","black","red","green","blue"})

#define SS_DRAGONARMY_ATTACK    143008
#define SS_DRAGONARMY_FUND      143009
#define SS_DRAGONARMY_PROMOTION 143021

#define PROMOTION_LEVELS ({"recruit","soldier","officer","high officer","general"})

#define ZERO_TITLES ({ "New Recruit", "Young Recruit", "Raw Recruit", \
    "Untrained Mercenary", "New Mercenary", "Blooded Mercenary", "Hardened Mercenary", })
#define ONE_TITLES ({ "Accepted Soldier", "Callous Soldier", "Toughened Soldier", \
	"Disciplined Soldier", "Decorated Soldier", })
#define TWO_TITLES ({ "New Dragon Rider", "Practised Dragon Rider", \
    "Accomplished Dragon Rider", "Talented Dragon Rider", \
    "Renowned Dragon Rider", "Feared Dragon Rider", })
#define THREE_TITLES ({ "Wing Commander", "High Commander", \
    "Dragon Master", "Dragon Highmaster", })

#define RED_TITLES ({ ZERO_TITLES, ONE_TITLES, \
({ \
"Untried Field Commander", \
"Adept Field Commander", \
"Successful Field Commander", \
"Dangerous Field Officer", \
"Accomplished Field Officer", \
"Brilliant Field Officer", \
}), ({ \
"Victorious Field Captain", \
"High Commander", \
"Dragon Master", \
"Dragon Highmaster", \
}), ({ \
"General of the Red Dragonarmies of Ansalon", \
}) })

#define BLUE_TITLES ({ ZERO_TITLES, ONE_TITLES, TWO_TITLES, THREE_TITLES, \
    ({ "General of the Blue Dragonarmies of Ansalon", }) })

#define GREEN_TITLES ({ ZERO_TITLES, ONE_TITLES, TWO_TITLES, THREE_TITLES, \
    ({ "General of the Green Dragonarmies of Ansalon", }) })

#define BLACK_TITLES ({ ZERO_TITLES, ONE_TITLES, TWO_TITLES, THREE_TITLES, \
    ({ "General of the Black Dragonarmies of Ansalon", }) })

#define WHITE_TITLES ({ ZERO_TITLES, ONE_TITLES, TWO_TITLES, THREE_TITLES, \
    ({ "General of the White Dragonarmies of Ansalon", }) })

// Dragonarmy Special Attacks
#define DRAGON_BREATH_SPECIAL   (DRAGONARMY_SPECIALS + "dragon_breath")
#define DRAGON_SWOOP_SPECIAL    (DRAGONARMY_SPECIALS + "dragon_swoop")
#define AUTOIMPALE_SPECIAL      (DRAGONARMY_SPECIALS + "autoimpale")
#define RDA_IMPALE_SPECIAL      (DRAGONARMY_SPECIALS + "rda_impale")
#define BDA_SLASH_SPECIAL       (DRAGONARMY_SPECIALS + "bda_slash")
#define AUTOIMPALE_STUN         (DRAGONARMY_SPECIALS + "autoimpale_stun")

// Skill manager for Dragonarmy
#define SKILL_MANAGER (DRAGONARMY_LIB + "dragonarmy_skill_manager")
// Manager for all Strike Dragons
#define DRAGONS_MANAGER (DRAGONARMY_LIB + "dragonarmy_dragon_manager")
// Dragon types
#define STRIKE_DRAGON   (DRAGONARMY_DRAGON + "strike_dragon")
#define DRAGON_STEED    (DRAGONARMY_DRAGON + "dragon")

// Property Defines
#define PENDING_DRAGON_SPECIAL  ("_dragonarmy_dragon_pending_remove")

#endif DRAGONARMY_DEFS
