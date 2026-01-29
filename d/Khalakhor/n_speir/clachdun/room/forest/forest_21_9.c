#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_20_8", "northwest");
    add_forest_exit(FOREST_DIR + "forest_20_10", "southwest");
}
