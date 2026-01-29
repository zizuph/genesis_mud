#include "../defs.h"

inherit "/d/Emerald/lib/ship_room";
inherit DOCK_ROOM;

void
create_dock_room()
{
    mkdock("Telberin");
    add_exit("../dock09", "east");
    set_ship_file(DOCK_DIR + "telberin/ship");
    add_ship();
}
