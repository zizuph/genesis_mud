#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_27_13", "north");
    add_forest_exit(FOREST_DIR + "forest_28_13", "northeast");
    add_forest_exit(FOREST_DIR + "forest_27_15", "south");
}
