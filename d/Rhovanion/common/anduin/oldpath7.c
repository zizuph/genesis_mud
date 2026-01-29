inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Edge of Mirkwood");
    set_long("Massive black-leaved trees loom over the path here as you " +
        "stand at the break between Anduin and Mirkwood Forest.  Shadows " +
        "cling to your hands and shroud the area in darkness. "+
        "To the east you can enter the dark Mirkwood following "+
        "the road called Men-i-Naugrim. But the time when this road "+
        "was frequently used and safe has long gone. So maybe you should "+
        "turn north and seek some safer way through this cursed forest.\n");

    add_exit(ANDUIN_DIR + "oldpath6", "west");
    add_exit(MIRK_DIR+"mirk-3-18-M", "east");
    add_exit(ANDUIN_DIR + "p1", "north");

    add_item(({ "path" }),
        "The path runs west to the Misty Mountains, and " +
        "enters Mirkwood Forest right here.\n");

    add_item(({ "trees", "black trees" }),
        "These trees are huge and silent, and you feel a " +
        "deep hatred for all things fair emenating from them.\n");

    add_item(({ "shadows", "shadow" }),
        "Deep shadows cover the area in a dark brooding gloom.\n");
}
