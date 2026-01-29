#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("rmc/dock", "east");
    add_exit("dock01", "north");
    add_exit("dock03", "southwest");
}
