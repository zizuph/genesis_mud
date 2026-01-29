#include "defs.h"

inherit MIST_SHORE_BASE;

public void
create_mist_shore_room()
{
    add_mist_exit(LSHORE_EXIT, MIST_TOWER_DIR + "mist_isle01",
        "southeast");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle03", "east");
    add_mist_exit(RSHORE_EXIT, MIST_TOWER_DIR + "mist_isle07", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle08", "north");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle09", "northeast");
}
