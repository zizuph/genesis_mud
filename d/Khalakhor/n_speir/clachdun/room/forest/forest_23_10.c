#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_23_9", "north");
    add_forest_exit(FOREST_DIR + "forest_24_9", "northeast");
    add_forest_exit(FOREST_DIR + "forest_24_11", "southeast");
}
