#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_22_19", "west");
    add_forest_exit(FOREST_DIR + "forest_24_18", "northeast");
    add_forest_exit(FOREST_DIR + "forest_23_20", "south");
}
