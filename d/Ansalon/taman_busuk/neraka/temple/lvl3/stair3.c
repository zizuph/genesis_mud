#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on the third floor landing of a spiraling " +
        "stone stairway in the Temple of Darkness. A winding corridor " +
        "lead off to the south, and the stairway continues both up and " +
        "down.\n");

    add_exit( LVLTHREE + "corr1.c", "south" );
    add_exit( LVLFOUR + "stair4.c", "up" );
    add_exit( LVLTWO + "stair2.c", "down" );
}
