#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_exit(FOREST_DIR + "forest_22_15", "southwest");
    add_exit(FOREST_DIR + "forest_22_14", "west");
    add_exit(FOREST_DIR + "forest_22_13", "northwest");
}
