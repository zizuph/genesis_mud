#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_20_4", "northwest");
    add_forest_exit(FOREST_DIR + "forest_22_4", "northeast");
    add_forest_exit(FOREST_DIR + "forest_21_6", "south");
}
