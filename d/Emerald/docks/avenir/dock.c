#include "../defs.h"

inherit DOCK_ROOM;

void
create_dock_room()
{
   mkdock(AVENIR_LINE);
    add_exit("../dock15", "southwest");
}
