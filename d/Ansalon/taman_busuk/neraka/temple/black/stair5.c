#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("Top of a winding stairway");
    set_long("You are at the top of a spiraling stone stairway. It " +
        "ends here abruptly and leads only down.\n");

    add_exit(BLACK + "stair4.c", "down" );
}
