#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_21_5", "north");
    add_forest_exit(FOREST_DIR + "forest_22_7", "southeast");
}
