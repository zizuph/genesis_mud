#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_23_5", "southeast");
    add_forest_exit(FOREST_DIR + "forest_21_5", "southwest");
}
