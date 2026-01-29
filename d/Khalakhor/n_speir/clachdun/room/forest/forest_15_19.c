#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_14_20", "southwest");
    add_forest_exit(FOREST_DIR + "forest_16_18", "northeast");
}
