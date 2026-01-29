#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_20_8", "northeast");
    add_forest_exit(FOREST_DIR + "forest_19_10", "south");
    add_forest_exit(FOREST_DIR + "forest_18_10", "southwest");
}
