#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_20_7", "north");
    add_forest_exit(FOREST_DIR + "forest_19_9", "southwest");
    add_forest_exit(FOREST_DIR + "forest_21_9", "southeast");
}
