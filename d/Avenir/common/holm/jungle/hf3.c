// file name:        /d/Avenir/common/holm/jungle/hf3.c
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

int climb_down();

/* Now create the room.  */
void
create_hf_room()
{
    set_short("Near the entrance to a crevice");
    set_long("You stand at the top of the cliff, overlooking " +
        "an avalanche far below. Tiny cones like deer "+
        "droppings litter the ground beneath the tortured "+
        "figures of stunted pine trees. Lichen mottles the "+
        "exposed surface of the black stone, resembling "+
        "putrid yellow scabs waiting to be picked. There "+
        "is a crevice at your feet, leading downward into "+
        "shadowy darkness.\n");

    add_avalanche();
    add_lichen();
    add_moss();
    add_crevice();

    add_exit("hf2", "north", 0);
    add_exit("hf4", "down", climb_down);
    reset_domain_room();
}

int
climb_down()
{
    write("\nYou lower yourself into the crevice and "+
        "climb down using the hollows carved into the "+
        "stone.\n\n");
   return 0;
}

