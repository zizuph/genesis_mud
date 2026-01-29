#include "../defs.h"

inherit DOCK_ROOM;
inherit "/d/Emerald/lib/ship_room";

void
create_dock_room()
{
    mkdock(FAERIE_LINE);
    add_exit("../dock14", "south");
    set_ship_file(DOCK_DIR + "faerie/ship");
    add_ship();
}
