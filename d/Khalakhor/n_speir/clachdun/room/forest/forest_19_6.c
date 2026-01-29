#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_19_5", "north");
    add_forest_exit(FOREST_DIR + "forest_20_7", "southeast");
    add_forest_exit(FOREST_DIR + "forest_19_7", "south");
}
