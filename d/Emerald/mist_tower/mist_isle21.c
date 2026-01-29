#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle20", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle25", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle26", "northeast");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle22", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle16", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle15", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle14", "southwest");
}
