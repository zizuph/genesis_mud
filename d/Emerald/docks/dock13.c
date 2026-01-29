#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("dock14", "east");
    add_exit("dock12", "west");
    add_door_exit(DOCK_DOOR_OBJ, "pav2", "south");
}
