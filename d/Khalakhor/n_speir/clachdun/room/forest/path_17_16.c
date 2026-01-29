#include "local.h"

inherit PATH_BASE;

void
create_path()
{
    add_exit(FOREST_DIR + "forest_18_15", "northeast", 0, 1, 1);
    add_exit(FOREST_DIR + "forest_16_17", "southwest", 0, 1, 1);
    add_exit(FOREST_DIR + "path_16_15", "northwest");
    add_exit(FOREST_DIR + "path_18_17", "southeast");
}
