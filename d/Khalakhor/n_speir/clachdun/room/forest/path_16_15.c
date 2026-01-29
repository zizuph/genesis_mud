#include "local.h"

inherit PATH_BASE;

void
create_path()
{
    add_exit(ROOM_DIR + "barrack_15_14", "northwest");
    add_exit(FOREST_DIR + "path_17_16", "southeast");
}
