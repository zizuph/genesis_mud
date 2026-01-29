#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_15_18", "northeast");
    add_forest_exit(FOREST_DIR + "forest_14_18", "north");
    add_forest_exit(FOREST_DIR + "forest_14_20", "south");
    add_forest_exit(FOREST_DIR + "forest_13_19", "west");
}
