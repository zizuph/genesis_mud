// file name:        /d/Avenir/common/holm/jungle/hf9.c
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
    set_short("On a ridge overlooking the forest");
    set_long("You stand on a weathered stone ridge overlooking a "+
        "vast lowland forest. Innumerable small plants grow "+
        "here, impeding your progress with their constant "+
        "presence underfoot. Tiny cones like deer droppings "+
        "litter the ground beneath the tortured figures of "+
        "stunted pine trees.\n");

    add_ridge();

    add_exit("hf10", "east", 0);
    add_exit("hf8", "west", 0);

    reset_domain_room();
}
