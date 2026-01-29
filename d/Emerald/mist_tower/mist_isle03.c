#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle02", "west");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle01", "south");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle08", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "northeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle04", "east");
}
