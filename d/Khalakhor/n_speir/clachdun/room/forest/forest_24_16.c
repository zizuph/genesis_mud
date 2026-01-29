#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_25_15", "northeast");
    add_forest_exit(FOREST_DIR + "forest_23_15", "northwest");
    add_forest_exit(FOREST_DIR + "forest_23_17", "southwest");
}
