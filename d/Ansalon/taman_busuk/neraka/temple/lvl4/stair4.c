#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on a small landing in the middle of a spiral " +
        "stairway inside a high tower in the Temple of Darkness. The " +
        "continue both up and down.\n");

    add_exit( LVLFIVE + "stair5.c", "up" );
    add_exit( LVLTHREE + "stair3.c", "down" );
}
