#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_exit(FOREST_DIR + "path_17_16", "southwest");
    add_forest_exit(FOREST_DIR + "forest_19_14", "northeast");
}
