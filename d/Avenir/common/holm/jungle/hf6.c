// file name:        /d/Avenir/common/holm/jungle/hf6.c
// creator(s):       Lilith, Dec 96
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/hf_base";

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
create_hf_room()
{
    set_short("Ridge with pine trees");
    set_long("You stand on a rocky ridgetop. Trees on both sides "+
        "of the ridge are stunted and gnarled, sculpted by "+
        "an unseen hand into tortured shapes which seem to "+
        "silently scream the agony of their existence. There "+
        "is a jagged rent in the cliffside to the west. Tiny "+
        "cones like deer droppings litter the trail.\n");

    add_avalanche();
    add_crevice();
    add_ridge();

    add_exit("hf10", "southwest", 0);
    add_exit("hf7", "west", 0);
    add_exit("hf5", "north", 0);

    add_item("path", "It follows the ridge.\n");
    reset_domain_room();
}