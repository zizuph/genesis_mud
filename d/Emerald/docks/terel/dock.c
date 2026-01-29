#include "../defs.h"

inherit "/d/Emerald/lib/ship_room";
inherit DOCK_ROOM;

void
create_dock_room()
{
    mkdock(TEREL_LINE);
    add_exit("../dock12", "south");
    set_ship_file(DOCK_DIR + "terel/ship");
    add_ship();
}
