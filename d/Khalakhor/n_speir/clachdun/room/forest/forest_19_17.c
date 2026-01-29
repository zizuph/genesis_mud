#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_19_16", "north");
    add_forest_exit(FOREST_DIR + "forest_20_17", "east");
    add_forest_exit(FOREST_DIR + "path_18_17", "west");
}
