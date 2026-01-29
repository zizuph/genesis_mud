#include "defs.h"

inherit MIST_SHORE_BASE;

public void
create_mist_shore_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle14", "northeast");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle08", "east");
    add_mist_exit(LSHORE_EXIT, MIST_TOWER_DIR + "mist_isle02", "southeast");
}
