#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_19_13", "north");
    add_forest_exit(FOREST_DIR + "forest_20_15", "southeast");
    add_forest_exit(FOREST_DIR + "forest_18_15", "southwest");
}
