#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_21_18", "north");
    add_forest_exit(FOREST_DIR + "forest_22_19", "east");
}
