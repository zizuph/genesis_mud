#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_26_9", "north");
    add_forest_exit(FOREST_DIR + "forest_27_11", "southeast");
    add_forest_exit(FOREST_DIR + "forest_25_11", "southwest");
}
