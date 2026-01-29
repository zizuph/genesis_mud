#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

object door;

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("Inside the Red Dragonarmy entrance of the temple");
    set_long("You are standing in a section of a corridor leading north" +
        "east further into the Temple of Darkness. To the southwest " +
        "stands a heavy oak door serving as entrance for the Red " +
        "Dragonarmy into the temple and beyond that the grand city of " +
        "Neraka. The walls are lined with torches which shed some light " +
        "into the dark depths of the corridor and the floor is bare.\n"); 

    add_item(({"entrance"}),
        "The entrance is quite large and has a heavy oak door which " +
        "can be closed and barred from the inside if needed.\n");

    add_item(({"city", "Neraka"}),
        "You look towards the entranceand beyond the guards you catch " +
        "a small glimpse of the city outside.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "further into the temple.\n");

    setuid();
    seteuid(getuid());

    door = clone_object(DOOR + "raent1");
    door->move(this_object());

    add_exit( RED + "corr1.c", "northeast" );
}

string
door_cond() { return door->door_cond(); }
