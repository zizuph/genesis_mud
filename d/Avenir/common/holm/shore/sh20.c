// file name:        /d/Avenir/common/holm/shore/sh20.c
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
    set_short("Wave-swept rocky shoreline, strewn with seaweed.");
    set_long("This shore is pummeled by waves as they tumble past "+
        "the rocks offshore. Bunches of seaweed roll hypnotically "+
        "in the tide, carried forward with the flow and swept back "+
        "as the waves recede. Sand and sea sparkle in the diffuse "+
        "light of the Source, dazzling your eyes."+
        "\n");
    add_beachs();
    add_flotsam();
    add_rocks();
    add_exit("sh18", "north", 0);
    add_exit("sh19", "northeast", 0);
    add_exit("sh21", "east", 0);
    add_exit("sh22", "southwest", 0);
    reset_domain_room();
}

