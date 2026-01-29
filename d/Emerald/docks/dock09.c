#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("telberin/dock", "west");
    add_exit("dock10", "north");
    add_exit("dock08", "south");
    add_door_exit(DOCK_DOOR_OBJ, "pav1", "east");
}
