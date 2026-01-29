#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_26_16", "east");
    add_forest_exit(FOREST_DIR + "forest_24_17", "southwest");
}
