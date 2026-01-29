#include "defs.h"

inherit MIST_ROCK_BASE;

public void
create_mist_rock_room()
{
    add_mist_exit(ASHORE_EXIT | RROCK_EXIT,
        MIST_TOWER_DIR + "mist_isle26", "east");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle22", "southeast");
    add_mist_exit(TSHORE_EXIT, MIST_TOWER_DIR + "mist_isle21", "south");
    add_mist_exit(TSHORE_EXIT | LROCK_EXIT,
        MIST_TOWER_DIR + "mist_isle20", "southwest");
}
