#ifndef MIST_TOWER_DEFS
#define MIST_TOWER_DEFS

#include "/d/Emerald/sys/paths.h"
#include <stdproperties.h>

#define MIST_ISLE_BASE       (MIST_TOWER_DIR + "mist_isle")
#define MIST_SHORE_BASE      (MIST_TOWER_DIR + "mist_isle_shore")
#define MIST_ROCK_BASE       (MIST_TOWER_DIR + "mist_isle_rocks")
#define MIST_PROMINENCE_BASE (MIST_TOWER_DIR + "prominence")
#define MIST_TOWER_BASE      (MIST_TOWER_DIR + "tower")

#define CAN_SEE_IN_MIST(ob) \
    (ob->query_vampire() || ob->query_prop("_live_i_see_on_mist_isle"))
#define CAN_SEE_GROUND(ob) \
    (CAN_SEE_IN_MIST(ob) || ob->query_prop(CONT_I_HEIGHT) <= 140)
#define CAN_SEE_TOWER(ob) \
    (ob->query_vampire() || ob->query_magic_res(MAGIC_I_RES_ILLUSION) >= 99)

#define TSHORE_EXIT 1
#define ASHORE_EXIT 2
#define RROCK_EXIT  4
#define LROCK_EXIT  16
#define RSHORE_EXIT 32
#define LSHORE_EXIT 64

#endif
