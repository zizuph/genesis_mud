#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_19_14", "south");
    add_forest_exit(FOREST_DIR + "forest_19_12", "north");
}
