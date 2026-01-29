#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_16_17", "north");
    add_forest_exit(FOREST_DIR + "forest_15_19", "southwest");
}
