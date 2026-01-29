/* Please place some guards here to stop intruders. It would be nice if 
 * they allow clergy to enter and those who are in the clergy's team. 
 * Or some other thing to identify them as being allowed to enter. So that
 * we can let for instance applicants further into the guild or the like.
 */

#pragma strict_types

#include "defs.h"

inherit TEMPLE + "std_temple.c";

void
create_temple_room()
{
    

    ::create_temple_room();

     set_short("In a corridor in the temple");
    set_long("You are standing in a corridor leading west to the wide " +
        "corridor for pilgrims. This corridor is about 12 feet wide " +
        "with the vaulted ceiling rising 15 feet above your head. The " +
        "flickering light from the torches along the black walls are " +
        "mirrored off the polished marble floor creating disturbing " +
        "movements of shadows all around you. The corridor continues " +
        "to the east.\n");

    add_exit( TEMPLE + "corr5.c", "east" );
    add_exit( TEMPLE + "corr3.c", "west" );
}
