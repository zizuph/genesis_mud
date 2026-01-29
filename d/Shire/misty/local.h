#include "/d/Shire/sys/defs.h"

// Here for moving purposes
#define KEEP_ANGMAR_IN_RHOVANION

#define LORD_WIELDS_HALBERD


#define MISTY_ARM_DIR   MISTY_DIR + "arm/"
#define MISTY_NPC_DIR   MISTY_DIR + "npc/"
#define MISTY_OBJ_DIR   MISTY_DIR + "obj/"
#define MISTY_STD_DIR   MISTY_DIR + "std/"
#define MISTY_WEP_DIR   MISTY_DIR +"wep/"

#define NEW_ANGMAR      (MISTY_DIR + "new_angmar/")

#ifdef KEEP_ANGMAR_IN_RHOVANION
#undef ANGMAR_GUILD_DIR
#define ANGMAR_GUILD_DIR "/d/Rhovanion/common/misty/"
#endif
#define CAVE_DIR  MISTY_DIR + "goblin_caves/"
#define GOBLIN_NPC_DIR  MISTY_NPC_DIR

#define CAVE_BASE (MISTY_STD_DIR + "cave_base")
#define CAVE_GUARD_ROOM (MISTY_STD_DIR + "guard_room_base")
#define GOBLIN_BASE (MISTY_STD_DIR + "goblin_base")
#define MISTY_BASE (MISTY_STD_DIR + "misty_base")

#define MIRROR_CHECK        "_mirror_check_"
