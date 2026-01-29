#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle20", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle21", "northeast");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle15", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle08", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle07", "southwest");
}
