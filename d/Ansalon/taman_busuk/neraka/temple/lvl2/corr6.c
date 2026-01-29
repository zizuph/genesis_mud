#pragma strict_types

#include "../defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    object door;
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a corridor inside the Temple of " +
        "Darkness. It is about 12 feet wide with the vaulted ceiling " +
        "rising 15 feet above your head. Flickering light from the torches " +
        "along the black walls are mirrored off the polished marble floor " +
        "creating disturbing movements of shadows all around you. The " +
        "corridor leads off to the west.\n");

    add_exit( LVLTWO + "corr5.c", "west" );

    door = clone_object( DOOR + "office2a.c" );
    door->move(this_object());
}
