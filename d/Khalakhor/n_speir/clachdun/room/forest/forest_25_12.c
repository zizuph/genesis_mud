#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_26_12", "east");
    add_forest_exit(FOREST_DIR + "forest_24_13", "southwest");
    add_forest_exit(FOREST_DIR + "forest_24_11", "northwest");
}
