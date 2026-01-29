#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle07", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle14", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle15", "northeast");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle03", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle02", "south");
}
