#pragma strict_types

inherit "/d/Gondor/common/room.c";

#include <stdproperties.h>

#include "/d/Gondor/defs.h"

void
create_room()
{
    set_short("a poor section of Pelargir");

    set_long(BSN("You are on a section of street in Pelargir that is "
      + "populated entirely by shacks and shanties. The people here "
      + "are obviously too poor to afford much, though they do not seem "
      + "to mind a whole lot. The street continues to the east, though "
      + "unfortunately the western section is barricaded off by "
      + "construction. A small side street goes north."));

    add_item("construction", BSN("It consists of many stone bricks, "
      + "quite a few timbers, and no small amount of grime."));

    add_exit(PELAR_DIR + "street/proad2", "north",     0);
    add_exit(PELAR_DIR + "homes/shack2",  "northeast", 0);
    add_exit(PELAR_DIR + "street/proad4", "east",      0);
}










