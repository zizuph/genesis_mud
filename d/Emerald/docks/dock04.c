#include "defs.h"

inherit DOCK_PATH_ROOM;

void
create_dock_path_room()
{
    add_cargo_dock_exit("south");
    add_exit("dock03", "northeast");
    add_exit("dock05", "west");
}
