#include "defs.h"

inherit PAV_PATH_ROOM;

void
create_pavpath_room()
{
    add_exit("pav5", "east");
    add_door_exit(DOCK_DOOR_OBJ, "dock09", "west");
}
