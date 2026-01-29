#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_28_16", "northeast");
    add_forest_exit(FOREST_DIR + "forest_26_18", "southwest");
}
