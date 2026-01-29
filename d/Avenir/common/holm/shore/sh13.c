// file name:        /d/Avenir/common/holm/shore/sh13.c
// creator(s):       Lilith, April 97
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/shore/shore_base";

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
create_shore_room()
{
    set_short("Black sand beach strewn with seaweed");
    set_long("A broad black sand beach abutting a naturally-"+
        "occuring seawall. Waves whisper and rush against the "+
        "sand, leaving bits of seaweed behind. Farther out to "+
        "sea, jagged rocks sparkle and flash in the diffuse "+
        "light of the Source.\n");
    add_beachs();
    add_flotsam();
    add_rocks();
    add_exit("sh10", "northeast", 0);
    add_exit("sh14", "southwest", 0);
    reset_domain_room();
}

