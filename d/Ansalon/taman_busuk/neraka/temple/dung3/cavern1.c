/* This room should be _extremely_ well guarded. */

#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("Underground cavern");
    set_long("This is the underground cavern deep below the temple.\n");

    door = clone_object( DOOR + "cavern2.c" );
    door->move(this_object());
}
