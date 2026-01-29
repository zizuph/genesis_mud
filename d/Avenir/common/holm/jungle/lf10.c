// file name:        /d/Avenir/common/holm/jungle/lf10.c
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
    set_short("in a hollow, following a stream");
    set_long("Tufts of greenery spread along the stream's edge. "+
        "The water's surface is deceptively still, pulled taut "+
        "against the deep unrest beneath. The dark stone of "+
        "the cliff gleams darkly, glistening with condensed "+
        "water. Lacy leaf shadows dapple the ground.\n");

    add_exit("lf7", "northeast", 0);
    add_exit("lf13", "south", 0);

    add_prop(ROOM_I_TYPE, ROOM_BEACH);
    add_cliff();
    add_moss();
    add_atrack();
    add_stream();
    add_grass();

    reset_domain_room();
}


