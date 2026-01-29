inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("East of Anduin");
    set_long("The grass is thicker on this side of the river, wilder and " +
        "tougher.  The long grass sways in the wind.  To the east Mirkwood " +
        "Forest encroaches on the land.  Looking far to the northeast you " +
        "see what looks like a large house.  Back west reeds float lazily " +
        "in the Anduin.  You can follow the east bank of the river to the " +
        "north and south.\n");

    add_exit(ANDUIN_DIR + "oldpath3", "west");
    add_exit(ANDUIN_DIR + "n1e1", "north", "@@block");
    add_exit(ANDUIN_DIR + "togon1", "south");
/*
    add_exit(ANDUIN_DIR + "s1e1", "south", "@@block");
*/
    add_exit(ANDUIN_DIR + "oldpath5", "east");
}

int block()
{
    write("The vale of Anduin has been flooded by an unusually rainy " +
        "season.  You could try back later when it has " +
        "had a chance to dry out some.\n");

    return 1;
}
