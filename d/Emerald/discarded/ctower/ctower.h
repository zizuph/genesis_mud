#ifndef CTOWER_DEFS
#define CTOWER_DEFS

#include "/d/Emerald/defs.h"

#define CTOWER_QUEST_NAME "crystal_torque"

#undef CTOWER_DIR
#define CTOWER_DIR "/d/Emerald/ctower/"

#define	TOWER_LOG	    "/d/Emerald/log/tower"
#define CTOWER_LOG          CTOWER_DIR + "log/"
#define CTOWER_NPC          CTOWER_DIR + "npc/"
#define CTOWER_OBJ          CTOWER_DIR + "obj/"
#define CTOWER_WEP          CTOWER_DIR + "wep/"
#define CTOWER_ARM          CTOWER_DIR + "arm/"
#define CTOWER_ROOM         CTOWER_DIR + "room/"
#define CTOWER_ROOM_MAZE    CTOWER_ROOM + "maze/"
#define CTOWER_ROOM_FIN     CTOWER_ROOM + "fin/"
#define CTOWER_ROOM_ELEM    CTOWER_ROOM + "elements/"
#define CTOWER_ROOM_LIBRARY CTOWER_ROOM + "library/"

// The .c extensions are necessary.  Please do not remove them
#define MAZESTD  CTOWER_ROOM_MAZE    + "mazestd.c"
#define FINSTD   CTOWER_ROOM_FIN     + "finstd.c"
#define LIBSTD   CTOWER_ROOM_LIBRARY + "libstd.c"
#define WATERSTD CTOWER_ROOM_ELEM    + "waterstd.c"
#define FIRESTD  CTOWER_ROOM_ELEM    + "firestd.c"
#define AIRSTD   CTOWER_ROOM_ELEM    + "airstd.c"
#define EARTHSTD CTOWER_ROOM_ELEM    + "earthstd.c"
#define ELEMSTD  CTOWER_ROOM_ELEM    + "elemstd.c"

#define CTOWER_MANAGER (CTOWER_DIR + "ctower_manager")

#define ELEMENTAL_DAMAGE (CTOWER_ROOM_ELEM + "elem_damage")

#define LIVE_I_KILLED_IMAGE "_live_i_killed_image"

#endif
