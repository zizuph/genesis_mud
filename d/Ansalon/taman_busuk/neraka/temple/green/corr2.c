#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a corridor in the temple which opens " +
        "up into a larger chamber to the southeast. To the northwest is " +
        "a winding stairway and the corridor itself continues to the " +
        "west. The black walls are lined with torches which shed " +
        "some light along the corridor.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "towards the centre of the temple.\n");

    add_exit( GREEN + "stair1.c", "northwest" );
    add_exit( GREEN + "corr1.c", "west" );
    add_exit( GREEN + "achamber.c", "east" );
}

