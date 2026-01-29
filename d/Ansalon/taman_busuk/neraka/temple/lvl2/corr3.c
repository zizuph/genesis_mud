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
        "creating disturbing movements of shadows all around you. A small " +
        "archway lies to the south and the corridor continues to the " +
        "east while a small room opens up to the west.\n");

    add_exit( LVLTWO + "corr2.c", "east" );
    add_exit( LVLTWO + "abbey.c", "west" );
    add_exit( LVLTWO + "landing.c", "south","@@stair_notice", 0, 1 );

#ifdef 0
    door = clone_object( DOOR + "abbey1.c" );
    door->move(this_object());
#endif
}

int
stair_notice()
{
    write("You step through the small archway and descend the " +
        "narrow stairs.\n\n");
    return 0;
}

