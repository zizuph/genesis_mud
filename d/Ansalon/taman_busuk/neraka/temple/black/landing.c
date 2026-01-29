#pragma strict_types

#include "../defs.h"
#include <stdproperties.h>

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("On a small landing");
    set_long("You are standing on a small and dark landing. The walls are " +
        "dark and twisted and there are no torches on the walls to shed " +
        "any light. A short narrow stairway leads up to the " +
        "southeast.\n");
    add_item(({"walls", "wall"}), "The walls are made of black stone " +
        "streaked with dark-red veins almost black as dried blood.\n");

    add_exit( BLACK + "corr4.c", "southeast","@@stair_notice", 0, 1 );

    add_prop(ROOM_I_INSIDE, 0);

    door = clone_object( DOOR + "bkaplatf1.c");
    door->move(this_object());
}

int
stair_notice()
{
    write("You ascend the twisting stairs and step through the small " +
        "archway.\n\n");
    return 0;
}

