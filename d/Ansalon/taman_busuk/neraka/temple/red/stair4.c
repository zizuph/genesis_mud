#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on a landing of a spiraling stone " +
        "stairway which opens up to a huge balcony facing south. " +
        "The stairway continues both up and down.\n");

    add_exit( RED + "balcony", "south" );
    add_exit( RED + "stair5.c", "up" );
    add_exit( RED + "stair3.c", "down" );
}
