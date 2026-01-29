#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_stair.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("On a winding stairway");
    set_long("You are standing on a small landing in the middle of a spiral " +
        "stairway inside a high tower in the Temple of Darkness. The " +
        "corridor continues both up and down.\n");

    add_exit( BLUE + "stair4.c", "up" );
    add_exit( BLUE + "stair2.c", "down" );

    door = clone_object( DOOR + "bahigh1.c");
    door->move(this_object());

}
