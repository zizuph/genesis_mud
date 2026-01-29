#include "../defs.h"

inherit DOCK_ROOM;
inherit "/d/Emerald/lib/ship_room";

void
create_dock_room()
{
    mkdock(SPARKLE_LINE);
    add_exit("../dock16", "west");
    set_ship_file(DOCK_DIR + "sparkle/ship");
    add_ship();
}
