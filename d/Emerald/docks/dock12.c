#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("terel/dock", "north");
    add_exit("dock13", "east");
    add_exit("dock11", "southwest");
}
