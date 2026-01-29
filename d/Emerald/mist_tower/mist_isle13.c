#include "defs.h"

inherit MIST_ISLE_BASE;

public void
create_mist_isle_room()
{
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle12", "west");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle18", "northwest");
    add_mist_exit(ASHORE_EXIT, MIST_TOWER_DIR + "mist_isle19", "north");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle06", "southwest");
}
