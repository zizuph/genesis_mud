#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle21", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle26", "north");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle23", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle17", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle16", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle15", "southwest");
}
