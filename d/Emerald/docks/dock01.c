#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("dock02", "south");
    add_exit("dock16", "north");
    add_door_exit(DOCK_DOOR_OBJ, "pav3", "west");
}
