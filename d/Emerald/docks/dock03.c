#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_cargo_dock_exit("southeast");
    add_exit("dock02", "northeast");
    add_exit("dock04", "southwest");
}
