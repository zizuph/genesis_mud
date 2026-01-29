#include "local.h"

inherit FOREST_BASE;

void
create_forest()
{
    add_forest_exit(FOREST_DIR + "forest_21_16", "northeast");
    add_forest_exit(FOREST_DIR + "forest_21_18", "southeast");
    add_forest_exit(FOREST_DIR + "forest_19_17", "west");
}
