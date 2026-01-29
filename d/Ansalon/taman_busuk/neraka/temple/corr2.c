#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a wide corridor which leads pilgrims " +
        "into the Temple of Darkness. It continues south further into " +
        "the depths of this dark structure and north out into the city. " +
        "The corridor is wide and the ceiling is 20 feet high and vaulted. " +
        "The black walls are lined with torches and two rooms lie on " +
        "either side of the corridor.\n");

    add_item(({"city", "neraka"}),
        "It is impossible for you to see the city from here.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "towards the centre of the temple.\n");

    add_exit( TEMPLE + "corr1.c", "north" );
    add_exit( TEMPLE + "corr3.c", "south" );
    add_exit( TEMPLE + "guard2.c", "east" );
    add_exit( TEMPLE + "guard1.c", "west" );
}

