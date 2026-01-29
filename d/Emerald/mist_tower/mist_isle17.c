#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle16", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle22", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle23", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle24", "northeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle18", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle12", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "southwest");
}
