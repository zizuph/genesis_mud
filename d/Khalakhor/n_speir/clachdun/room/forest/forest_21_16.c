#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_22_17", "southeast");
    add_forest_exit(FOREST_DIR + "forest_20_15", "northwest");
    add_forest_exit(FOREST_DIR + "forest_20_17", "southwest");
}
