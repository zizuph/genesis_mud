#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on a landing of a spiraling stone " +
        "stairway which opens up to a huge balcony facing east. " +
        "The stairway continues both up and down.\n");

    add_exit( BLUE + "balcony", "east" );
    add_exit( BLUE + "stair5.c", "up" );
    add_exit( BLUE + "stair3.c", "down" );
}
