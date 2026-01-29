#include "defs.h"

inherit PAV_PATH_ROOM;

void
create_pavpath_room()
{
    add_exit("pav7", "west");
    add_door_exit(DOCK_DOOR_OBJ, "dock01", "east");
}
