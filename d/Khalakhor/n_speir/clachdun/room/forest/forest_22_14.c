#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_exit(FOREST_DIR + "forest_22_13", "north");
    add_exit(FOREST_DIR + "forest_23_14", "east");
    add_exit(FOREST_DIR + "forest_22_15", "south");
    add_exit(FOREST_DIR + "forest_21_14", "west");
}
