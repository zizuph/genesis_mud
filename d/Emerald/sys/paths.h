#ifndef EMERALD_PATHS_HEADER
#define EMERALD_PATHS_HEADER

#define HOME_DIR        "/d/Emerald/"
 
#define COMMON_DIR      HOME_DIR + "common/"
 
#define GUILD_DIR       COMMON_DIR + "guild/"
 
#define HELP_DIR        HOME_DIR + "help/"
 
#define EMERALD_WEP_DIR   HOME_DIR + "wep/"
#define EMERALD_ARM_DIR   HOME_DIR + "arm/"

#ifndef BLACKWALL_DIR
#define BLACKWALL_DIR    HOME_DIR + "blackwall/"
#endif

#ifndef BLACKWALL_VALLEY1_DIR
#define BLACKWALL_VALLEY1_DIR   BLACKWALL_DIR + "valley1/"
#endif

#ifndef CHAPEL_DIR
#define CHAPEL_DIR      HOME_DIR + "chapel/"
#endif

#ifndef DOCKS_DIR
#define DOCKS_DIR       HOME_DIR + "docks/"
#endif

#ifndef TELBERIN_DIR
#define TELBERIN_DIR    HOME_DIR + "telberin/"
#endif

#ifndef LEAH_DIR
#define LEAH_DIR        HOME_DIR + "leah/"
#endif

#ifndef CTOWER_DIR
#define CTOWER_DIR      HOME_DIR + "ctower/"
#endif

#ifndef DEL_RIMMON_DIR
#define DEL_RIMMON_DIR   BLACKWALL_DIR + "delrimmon/"
#endif

#ifndef MONASTERY_DIR
#define MONASTERY_DIR   HOME_DIR + "monastery/"
#endif

#ifndef MIST_TOWER_DIR
#define MIST_TOWER_DIR  HOME_DIR + "mist_tower/"
#endif

#ifndef VILLAGE_DIR
#define VILLAGE_DIR     HOME_DIR + "leah/"
#endif

#ifndef THIEF_LAIR_DIR
#define THIEF_LAIR_DIR  HOME_DIR + "thief_lair/"
#endif

#ifndef GRUNTS_DIR
#define GRUNTS_DIR    HOME_DIR + "grunts/"
#endif

#ifndef KOT_DIR
#define KOT_DIR         GUILD_DIR + "kot/"
#endif

#ifndef VAMP_DIR
#define VAMP_DIR        GUILD_DIR + "vamp/"
#endif

#define HERB_DIR        HOME_DIR + "herbs/"

#define BOARD_DIR       HOME_DIR + "boards/"
 
#define QUEST_LOG           "/d/Emerald/log/quest/quest"
#define DEBUGFILE           "/d/Emerald/sys/debug.h"
#define EMERALD_MONSTER     "/d/Emerald/std/emerald_monster"
#define EMERALD_MONSTER_OBJ EMERALD_MONSTER
#define EMERALD_DOOR_OBJ    "/d/Emerald/std/door"

#endif
