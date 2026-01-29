#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_26_15", "east");
    add_forest_exit(FOREST_DIR + "forest_24_16", "southwest");
}
