#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle17", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle18", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle19", "northeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle13", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle06", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle05", "southwest");
}
