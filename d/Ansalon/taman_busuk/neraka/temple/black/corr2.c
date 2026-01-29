#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a corridor in the temple which " +
        "continues both west and east. To the south is a " +
        "winding stairway and the black walls are lined with torches " +
        "which shed some light along the corridor.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "towards the centre of the temple.\n");

    add_exit( BLACK + "corr3.c", "west" );
    add_exit( BLACK + "corr1.c", "east" );
    add_exit( BLACK + "stair1.c", "south" );
}

