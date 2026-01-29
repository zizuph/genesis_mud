#include "defs.h"

inherit MIST_SHORE_BASE;

public void
create_mist_shore_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle03", "west");
    add_mist_exit(RSHORE_EXIT, MIST_TOWER_DIR + "mist_isle01", "southwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle10", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle11", "northeast");
    add_mist_exit(LSHORE_EXIT, MIST_TOWER_DIR + "mist_isle05", "east");
}
