#include "../defs.h"

inherit "/d/Emerald/lib/ship_room";
inherit DOCK_ROOM;

void
create_dock_room()
{
    mkdock("the northern shores");
    add_exit("../dock07", "northeast");
    set_ship_file(DOCK_DIR + "telberin/ship");
    add_ship();
}
