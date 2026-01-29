#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("dock12", "northeast");
    add_cargo_dock_exit("northwest");
    add_exit("dock10", "southwest");
}
