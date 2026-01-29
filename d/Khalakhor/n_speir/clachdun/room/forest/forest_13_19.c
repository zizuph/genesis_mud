#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_13_20", "south");
    add_forest_exit(FOREST_DIR + "forest_14_19", "east");
    add_forest_exit(FOREST_DIR + "forest_13_18", "north");
}
