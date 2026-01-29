#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle15", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle16", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle17", "northeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle05", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle04", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle03", "southwest");
}
