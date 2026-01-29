#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a corridor in the temple which " +
        "continues both northwest and southeast. To the southwest is a " +
        "winding stairway and the black walls are lined with torches " +
        "which shed some light along the corridor.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "towards the centre of the temple.\n");

    add_exit( BLUE + "corr3.c", "northwest" );
    add_exit( BLUE + "corr1.c", "southeast" );
    add_exit( BLUE + "stair1.c", "southwest" );
}

