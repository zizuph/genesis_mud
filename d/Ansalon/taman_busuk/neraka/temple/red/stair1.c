#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on the ground floor landing of a spiraling " +
        "stone stairway in the Temple of Darkness. To the east is a " +
        "shadowy corridor and the stairway leads both up and down.\n");

    add_exit( RED + "corr2.c", "east" );
    add_exit( RED + "stair2.c", "up" );
    add_exit( RED + "stair0.c", "down" );
}
