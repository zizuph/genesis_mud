#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on the ground floor landing of a spiraling " +
        "stone stairway in the Temple of Darkness. To the south is a " +
        "shadowy corridor and the stairway leads both up and down.\n");

    add_exit( WHITE + "corr2.c", "south" );
    add_exit( WHITE + "stair2.c", "up" );
    add_exit( WHITE + "stair0.c", "down" );
}
