#include "defs.h"

inherit MIST_SHORE_BASE;

public void
create_mist_shore_room()
{
    add_mist_exit(RSHORE_EXIT, MIST_TOWER_DIR + "mist_isle04", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle12", "northeast");
    add_mist_exit(LSHORE_EXIT, MIST_TOWER_DIR + "mist_isle06", "east");
}
