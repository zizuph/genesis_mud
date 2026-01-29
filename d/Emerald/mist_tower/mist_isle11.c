#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle16", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle17", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle18", "northeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle12", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle06", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle05", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle04", "southwest");
}
