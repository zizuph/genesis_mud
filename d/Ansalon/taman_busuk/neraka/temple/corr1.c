#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("Inside the entrance of the temple");
    set_long("You are standing in a section of a wide corridor leading " +
        "south further into the Temple of Darkness. To the north lie the " +
        "great gates of the temple and beyond those the grand city of " +
        "Neraka. The corridor is wide and the ceiling is 20 feet high " +
        "and vaulted. The black walls are lined with torches illuminating " +
        "the path for pilgrims visiting the temple.\n");

    add_item(({"gates", "great gates"}), 
        "To the north you see the large gates which can be closed to " +
        "cut off the main entrance to the Temple.\n");

    add_item("entrance", "The main entrance to the temple lies to the " +
        "north.\n");

    add_item(({"city", "neraka"}),
        "You look towards the gates and beyond the guards you catch a " +
        "small glimpse of the city outside.\n");

    add_item(({"corridor", "section", "path"}),
        "This part of the corridor is wide and seemingly straight, leading " +
        "towards the centre of the temple.\n");

    add_exit( TEMPLE + "entrance", "north" );
    add_exit( TEMPLE + "corr2.c", "south" );
}

