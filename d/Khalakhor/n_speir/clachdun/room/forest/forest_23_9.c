#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_23_8", "north");
    add_forest_exit(FOREST_DIR + "forest_23_10", "south");
}
