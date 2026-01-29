#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_25_20", "northeast");
    add_forest_exit(FOREST_DIR + "forest_23_20", "northwest");
}
