#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a corridor inside the Temple of " +
        "Darkness. It is about 12 feet wide with the vaulted ceiling " +
        "rising 15 feet above your head. Flickering light from the torches " +
        "along the black walls are mirrored off the polished marble floor " +
        "creating disturbing movements of shadows all around you. The " +
        "corridor continues both west and east where you see a spiral " +
        "stairway.\n");

    add_item(({"stairway", "spiral stairway"}),
        "To the east you see a winding spiral stairway lead both up and " +
        "down.\n");

    add_exit( TEMPLE + "stair1.c", "east" );
    add_exit( TEMPLE + "corr5.c", "west" );
}
