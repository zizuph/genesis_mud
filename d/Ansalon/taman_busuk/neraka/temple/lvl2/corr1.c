/* A door should lead off to the northwest from this room into a more 
 * private room which can be locked from the inside. ( LVLTWO + room1.c)
 */

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
        "creating disturbing movements of shadows all around you. A " +
        "stairway lies to the east. " +
#ifdef 0
        "An " +
        "archway to the north leads into a somewhat darker room and the " +
        "stairway lies to the east. 
#endif
        "The corridor continues both south and " +
        "west.\n");

    add_exit( LVLTWO + "corr5.c", "south" );
    add_exit( LVLTWO + "stair2.c", "east" );
    add_exit( LVLTWO + "corr2.c", "west" );
}
