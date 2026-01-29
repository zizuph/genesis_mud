#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_21_11", "north");
    add_forest_exit(FOREST_DIR + "forest_22_12", "east");
}
