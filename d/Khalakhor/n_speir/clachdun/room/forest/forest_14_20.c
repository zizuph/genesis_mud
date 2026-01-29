#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_13_20", "west");
    add_forest_exit(FOREST_DIR + "forest_14_19", "north");
    add_forest_exit(FOREST_DIR + "forest_15_19", "northeast");
}
