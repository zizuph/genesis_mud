#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on the second floor landing of a spiraling " +
        "stone stairway in the Temple of Darkness. A winding corridor " +
        "leads off to the west, and the stairway continues " +
        "both up and down.\n");

    add_exit( LVLTWO + "corr1.c", "west" );
    add_exit( LVLTHREE + "stair3.c", "up" );
    add_exit( TEMPLE + "stair1.c", "down" );
}
