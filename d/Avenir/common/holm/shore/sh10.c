// file name:        /d/Avenir/common/holm/shore/sh10.c
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
    set_long("Tufts of grass cling to the soft black sand "+
        "mounded against the "+
        "obsidian seawall and the stones of the promon"+
        "tory. A narrow passage, created by centuries "+
        "of water wear, leads east toward the jungle. "+
        "Waves whisper and hiss against the shoreline, "+
        "seeming to tease the patches of seaweed strand"+
        "ed in the sand.\n");
    add_beachs();
    add_flotsam();
    add_grass();
    add_exit("sh9", "northwest", 0);
    add_exit("sh11", "east", 0);
    add_exit("sh13", "southwest", 0);

    reset_domain_room();
}

