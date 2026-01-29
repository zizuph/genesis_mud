#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    object door;

    ::create_temple_room();

     set_short("On a small landing");
    set_long("You are standing on a small and dark landing. The walls are " +
        "dark and twisted and there are no torches on the walls to shed " +
        "any light. A short narrow stairway leads up north to an archway.\n");

    add_exit( LVLTWO + "corr3.c", "north","@@stair_notice", 0, 1 );

    door = clone_object( DOOR + "bridge1.c");
    door->move(this_object());
}

int
stair_notice()
{
    write("You ascend the narrow stairs and step through the small " +
        "archway.\n\n");
    return 0;
}
