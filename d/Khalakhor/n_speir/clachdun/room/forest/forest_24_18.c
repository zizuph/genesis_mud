#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_24_17", "north");
    add_forest_exit(FOREST_DIR + "forest_25_18", "east");
    add_forest_exit(FOREST_DIR + "forest_23_19", "southwest");
}
