// file name:        /d/Avenir/common/holm/shore/sh8.c
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
    set_short("Wave-swept black sand beach");
    set_long("Dried salt stains the dark sand with wavy "+
        "white lines, marking the ebb and flow of the tide. "+
        "The jagged backbone of the promontory thrusts itself "+
        "upward against the encroaching waters. Seaweed and "+
        "flotsam litter the beach.\n");
    add_beachp();
    add_flotsam();
    add_salt();
    add_exit("sh9", "southeast", 0);
    add_exit("sh7", "northwest", 0);
    reset_domain_room();
 }

