#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("A large empy room");
    set_long("This is a large empty room which the Highlord still has " +
        "not decorated.\n"); 

    door = clone_object( DOOR + "bkahigh2.c");
    door->move(this_object());
}
