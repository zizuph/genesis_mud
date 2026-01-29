#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle15", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle21", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle22", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle23", "northeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle17", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "southwest");
}
