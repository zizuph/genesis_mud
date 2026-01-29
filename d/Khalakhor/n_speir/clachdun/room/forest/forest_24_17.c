#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_25_16", "northeast");
    add_forest_exit(FOREST_DIR + "forest_24_18", "south");
}
