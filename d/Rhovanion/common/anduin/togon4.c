inherit "/d/Rhovanion/lib/room";

#include "/d/Rhovanion/defs.h"

create_room()
{
    set_short("East of Anduin");
    set_long("You are on the east bank of the Anduin. To the east, "+
             "a wide plain stretches towards dark Mirkwood visible in the distance. "+
             "You see a dark cloud hanging about a hill rising out of the Mirkwood.\n");

    add_exit(ANDUIN_DIR + "togon3", "north");
    add_exit(ANDUIN_DIR + "togon5", "southeast");
}
