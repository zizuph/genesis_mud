#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_exit(FOREST_DIR + "forest_22_14", "north");
    add_exit(FOREST_DIR + "forest_23_14", "northeast");
    add_exit(FOREST_DIR + "forest_21_14", "northwest");
}
