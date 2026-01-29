#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_cargo_dock_exit("southwest");
    add_exit("dock08", "northwest");
    add_exit("dock06", "southeast");
}
