#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on the bottom landing of a long " +
        "spiraling stone stairway in the Temple of Darkness. A dark " +
        "narrow corridor leads off south, and the stairway leads back up.\n");

    add_exit( DUNGTWO + "corr1.c", "south" );
    add_exit( DUNGONE + "stair0.c", "up" );
}
