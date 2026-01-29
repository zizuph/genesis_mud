inherit "/d/Rhovanion/lib/room";

#include <stdproperties.h>
#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("West of Mirkwood");
    set_long("@@mylong");

    add_exit(ANDUIN_DIR + "oldpath7", "east");
    add_exit(ANDUIN_DIR + "n1e3", "north", "@@block");
    add_exit(ANDUIN_DIR + "s1e3", "south", "@@block");
    add_exit(ANDUIN_DIR + "oldpath5", "west");
}

string mylong()
{
    string mess;

    if ((TP->query_alignment()) < 0)
        mess = "familiar and comforting";
    else
        mess = "dark and foreboding";

    mess = "In the west the Misty Mountains are only small bumps on the " +
        "horizon.  To the north and the south lies the Vale of Anduin.  " +
        "To the east-- Mirkwood forest, exuding an evil which is " + 
        mess + ".\n";

    return (BS(mess));
}

int block()
{
    write ("The vale of Anduin has been flooded by an unusually rainy season " +
        "season this year.  You could try back when it has had a chance to " +
       "dry out some.\n");

    return 1;
}
