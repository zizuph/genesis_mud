#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_25_8", "northwest");
    add_forest_exit(FOREST_DIR + "forest_26_10", "south");
}
