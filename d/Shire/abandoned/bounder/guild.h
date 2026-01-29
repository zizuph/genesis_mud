
//#include "defs.h"
//#include "lockout.h"

#define GUILD_NAME          "Bounders of the Shire"
#define GUILD_STYLE         "fighter"
#define GUILD_TAX           10

#define BOUND_DIR        "/d/Shire/bounders/"

#define BOUND_ROOM_DIR   BOUND_DIR + "room/"
#define BOUND_NPC_DIR    BOUND_DIR + "npc/"
#define BOUND_LOG_DIR    BOUND_DIR + "log/"
#define BOUND_OBJ_DIR    BOUND_DIR + "obj/"
#define BOUND_HELP_DIR   BOUND_DIR + "help/"
#define BOUND_SHADOW_DIR BOUND_DIR + "shadow/"
#define BOUND_SOUL_DIR   BOUND_DIR + "soul/"

#define BOUNDER_CMDSOUL  BOUND_DIR + "soul/bounder_soul.c"
#define BOUNDER_SHADOW   BOUND_DIR + "shadow/bounder_sh.c"

#define HOB_DIR          "/d/Shire/common/hobbiton/"

#define IS_MEMBER(x)   (x->query_guild_member(GUILD_NAME))