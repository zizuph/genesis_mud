#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_23_10", "northwest");
    add_forest_exit(FOREST_DIR + "forest_25_11", "east");
    add_forest_exit(FOREST_DIR + "forest_25_12", "southeast");
    add_forest_exit(FOREST_DIR + "forest_23_12", "southwest");
}
