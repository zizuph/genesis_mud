#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle08", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle14", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle15", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle16", "northeast");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle04", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle03", "south");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle02", "southwest");
}
