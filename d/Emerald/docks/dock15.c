#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_exit("avenir/dock", "northeast");
    add_exit("dock16", "southeast");
    add_exit("dock14", "northwest");
}
