#include "defs.h"

inherit MIST_SHORE_BASE;

public void
create_mist_shore_room()
{
    add_mist_exit(RSHORE_EXIT, MIST_TOWER_DIR + "mist_isle05", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle12", "north");
    add_mist_exit(LSHORE_EXIT, MIST_TOWER_DIR + "mist_isle13", "northeast");
}
