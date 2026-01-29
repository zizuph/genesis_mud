// file name:        /d/Avenir/common/holm/jungle/lf8.c
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
    set_short("Deep in a lowland forest");
    set_long("A heavy mist blankets the ground. Tree limbs "+
        "intertwine above, forming a green cathedral canopy of "+
        "breathtaking beauty. Mosses beard the trunks of trees "+ 
        "and vines dangle from limbs like locks of hair. Small "+
        "herbacious plants crowd the forest floor, nearly "+
        "obscuring the path you are following.\n");

    add_exit("lf5", "north", 0);
    add_exit("lf11", "south", 0);

    add_moss();
    add_atrack();
    reset_domain_room();
}
