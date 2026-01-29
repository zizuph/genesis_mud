#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_19_13", "south");
    add_forest_exit(FOREST_DIR + "forest_18_11", "northwest");
    add_forest_exit(FOREST_DIR + "forest_20_11", "northeast");
}
