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
        "creating disturbing movements of shadows all around you. Through " +
        "an archway to the south is a large room and the corridor continues " +
        "to the east.\n");

    add_item("archway", "The archway is decorated with smooth black " +
        "stone with small carvings.\n");
    add_item(({"carvings", "pattern", "vines", "thorny vines"}),
        "The carvings on the archway make up a pattern of thorny vines.\n");

    add_exit( LVLTWO + "corr5.c", "east" );
    add_exit( LVLTWO + "dorm.c", "south", 0, 0, 1);

    door = clone_object( DOOR + "office1a.c" );
    door->move(this_object());
}
