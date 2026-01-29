#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_23_19", "east");
    add_forest_exit(FOREST_DIR + "forest_21_19", "west");
}
