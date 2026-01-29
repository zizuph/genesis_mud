#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_exit(FOREST_DIR + "path_17_16", "northeast");
    add_forest_exit(FOREST_DIR + "forest_16_18", "south");
    add_forest_exit(FOREST_DIR + "forest_15_17", "west");
}
