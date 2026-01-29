// file name:        /d/Avenir/common/holm/jungle/lf16.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

/* Include the local area defines, etc */
#include "/d/Avenir/common/holm/holm.h"

/*
 * Function name: reset_domain_room
 * Description:   This function should be used for for reseting herbs
 */
void reset_domain_room()
{
    set_searched(0);
    ::reset_domain_room();
}

/* Now create the room.  */
void
create_jungle_room()
{
    set_short("a marshy area in the hollow");
    set_long("A narrow point in the hollow, where the ground "+
        "slopes steeply upward in all directions except to the "+
        "southwest. Sphagnum grows everywhere. Water fills "+
        "your footsteps and a pungent, yeasty smell assails "+
        "your nose. The canopy of the forest is high overhead, "+
        "nearly obscuring the light of the Source.\n");

    add_exit("lf15", "west", 0);

    add_item("sphagnum", "It is a spongy moss that holds large "+
        "quantities of water. The feathery plant appears reddish "+
        "where the forest canopy is thinnest, and dark green else"+
        "where.\n");

    add_cliff();
    add_moss();
    add_atrack();
    add_stream();
    add_grass();

    reset_domain_room();
}
