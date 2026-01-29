#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("sparkle/dock", "east");
    add_exit("dock01", "south");
    add_exit("dock15", "northwest");
}
