#include "../defs.h"

inherit DOCK_ROOM;

void
create_dock_room()
{
    mkdock("Golden Island");
    add_exit("../dock02", "west");
}
