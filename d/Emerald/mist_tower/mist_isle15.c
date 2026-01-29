#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle14", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle20", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle21", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle22", "northeast");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle16", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle08", "southwest");
}
