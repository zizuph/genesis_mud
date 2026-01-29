#pragma strict_types

#include "../defs.h"

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
        "creating disturbing movements of shadows all around you. An " +
        "archway to the southeast leads into another room and the corridor " +
        "continues north, east and west.\n");

    add_item("archway", "The archway is decorated with smooth black stone " +
        "with small carvings.\n");
    add_item(({"carvings", "pattern", "stars", "black stars"}),
        "The carvings on the archway make up a pattern of black stars.\n");

    add_exit( LVLTWO + "corr1.c", "north" );
    add_exit( LVLTWO + "corr6.c", "east" );
    add_exit( LVLTWO + "corr4.c", "west" );
    add_exit( LVLTWO + "library.c", "southeast" );
}
