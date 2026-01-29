#include "local.h"

inherit PATH_BASE;

void
create_path()
{
    add_exit(FOREST_DIR + "path_17_16", "northwest");
    add_exit(FOREST_DIR + "path_18_18", "south");
    add_exit(FOREST_DIR + "forest_19_17", "east", 0, 1, 1);
}
