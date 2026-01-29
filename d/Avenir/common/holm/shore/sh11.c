// file name:        /d/Avenir/common/holm/shore/sh11.c
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
    set_short("Narrow stretch of black sand between jagged stones");
    set_long("The path between the promontory stones and the "+
        "obsidian seawall is very narrow here, so your only choice "+
        "is to go east or west. The sand is soft "+
        "and powdery underfoot, making your progress difficult. "+
        "The wind whistles and moans high overhead, carrying the "+
        "sound of crashing surf to your ears.\n");
    add_beachs();
    add_rocks();
    add_exit("sh12", "east", 0, 5, 1);
    add_exit("sh10", "west", 0, 5, 1);
    reset_domain_room();
}

