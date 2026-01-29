// file name:        /d/Avenir/common/holm/jungle/lf6.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

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
    set_short("Northwest edge of a lowland forest");
    set_long("You are at the edge of a lowland forest. Ferns "+
        "and moss lay in a tangled wilderness under the trees, "+
        "partially obscuring an ancient track that slopes "+
        "upward to the south. A jagged obsidian wall blocks "+
        "the view of the sea to the west, but you can still "+
        "hear the lapping of the surf against the shore. A "+
        "cliff rises steeply in the southeast.\n");

    add_cliff();
    add_seawall();
    add_fern();
    add_moss();
    add_atrack();

    add_exit("lf1", "north", 0);
    add_exit("lf2", "northeast", 0);
    add_exit("lf9", "south", 0);
    
    reset_domain_room();
}

