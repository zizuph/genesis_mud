#include "defs.h"

inherit PAV_PATH_ROOM;

void
create_pavpath_room()
{
    add_exit("pav6", "south");
    add_door_exit(DOCK_DOOR_OBJ, "dock13", "north");
}
