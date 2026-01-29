inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("West of Mirkwood");
    set_long("The old path runs straight and wide through here, " +
        "but off in the distance it seems to narrow, and finally " +
        "disappear altogether beneath the hanging branches of the " +
        "trees of Mirkwood Forest.  Far to the north you see a solitary " +
        "house, standing defiantly on the edge of the forest.  " +
        "More of the plains of Anduin stand to the south, and the Misty " +
        "Mountains lie far to the west.\n");

    add_exit(ANDUIN_DIR + "oldpath4", "west");
    add_exit(ANDUIN_DIR + "n1e2", "north", "@@block");
    add_exit(ANDUIN_DIR + "s1e2", "south", "@@block");
    add_exit(ANDUIN_DIR + "oldpath6", "east");
}

int block()
{
    write ("The vale of Anduin has been flooded by an unusually rainy " +
        "season this year.  You could try back later when " +
        "it has had a chance to dry out some.\n");

    return 1;
}
