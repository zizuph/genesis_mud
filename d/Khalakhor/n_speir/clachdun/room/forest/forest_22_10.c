#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_21_9", "northwest");
    add_forest_exit(FOREST_DIR + "forest_21_11", "southwest");
}
