#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_21_12", "west");
    add_exit(FOREST_DIR + "forest_22_13", "south");
}
