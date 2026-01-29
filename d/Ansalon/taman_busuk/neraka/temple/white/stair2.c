#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on a landing of a spiraling stone " +
        "stairway. A winding corridor leads off to the east, and the " +
        "stairway continues both up and down.\n");

    add_exit( WHITE + "corr3.c", "east" );
    add_exit( WHITE + "stair3.c", "up" );
    add_exit( WHITE + "stair1.c", "down" );
}
