inherit "/d/Rhovanion/lib/room"; 

#include <stdproperties.h>
#include <macros.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("Bank of Anduin");
    set_long("To the east lies Anduin, the great river, and beyond " +
        "it, Mirkwood.  The river is shallow enough to be forded at " +
        "this spot, though it looks impassable to the north and the south.  " +
        "Back west lie the Misty Mountains, and the plains follow the " +
        "river north and south.\n");

    add_exit(ANDUIN_DIR + "n1w1", "north", "@@block");
    add_exit(ANDUIN_DIR + "s1w1", "south", "@@block");
    add_exit(ANDUIN_DIR + "oldpath1", "west");
    add_exit(ANDUIN_DIR + "oldpath3", "east");
}

int block()
{
    write("The vale of Anduin has been flooded by an unusually rainy " +
        "season.  You could try back later when it has had " +
        "a chance to dry out some.\n");

    return 1;
}
