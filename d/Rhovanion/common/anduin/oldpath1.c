inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Old path");
    set_long("This grassy path is surprisingly pleasant considering " +
        "how close to Mirkwood it is.  Back to the west are the " +
        "Misty Mountains, and to the east lurks Mirkwood forest.  " +
        "You can wander in the vale of Anduin to the north and the " +
        "south.  Looking north, you vaguely make out a tall spire of " +
        "rock.\n");

    add_exit(MISTY_DIR + "p13", "west");
    add_exit(ANDUIN_DIR + "oldpath2", "east");
    add_exit(ANDUIN_DIR + "n1w2", "north", "@@block");
    add_exit(ANDUIN_DIR + "s1w2", "south", "@@block");
}

int block()
{
    write("The vale of Anduin has been flooded by an unusually " +
        "rainy season.  You could try back later, when it has had a " +
        "chance to dry out some.\n");

    return 1;
}
