#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle17", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle23", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle24", "north");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle19", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle13", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle12", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "southwest");
}
