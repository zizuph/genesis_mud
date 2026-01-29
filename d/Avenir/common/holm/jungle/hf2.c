// file name:        /d/Avenir/common/holm/jungle/hf2.c
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
    set_short("Atop the cliff");
    set_long("You stand atop a cliff, with a view of the jungle "+
        "and an avalanche. The living stone humps up in "+
        "the southwest, looking like the spiny back of a "+
        "burrowing creature. A fringe of moss and vines "+
        "dangles over the lip of the cliff, and stunted "+
        "trees writhe their limbs in the steady breeze.\n");

    add_avalanche();
    add_moss();
    add_exit("hf1", "west", 0);
    add_exit("hf3", "south", 0);

    add_item(({"pool", "water", "west", "below"}), 
        "The pool of water resembles a small puddle"+
        " from this height. Its center whirls ominously.\n");
    add_item(({"path", "well-worn path"}),
        "This path continues south toward the face of cliff "+
        "and curves east toward the crevice.\n");
    reset_domain_room();
}