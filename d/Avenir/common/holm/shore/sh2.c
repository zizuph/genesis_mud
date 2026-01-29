// file name:        /d/Avenir/common/holm/shore/shore2.c
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
    set_short("Black sand beach along rocky shoreline");
    set_long("This is a narrow strand of pebbled beach, "+
        "framed in the west by the looming stones of the "+
        "promontory that extends northwest into the sea. "+
        "The obsidian wall lies both west and south, and "+
        "you can just glimpse the jungle through a narrow "+
        "passage leading southwest. Waves sweep the dark "+
        "shore, leaving bits of flotsam and seaweed in "+
        "their wake.\n");
    add_rocks();
    add_beachp();
    add_flotsam();
    add_exit("sh1", "east", 0);
    add_exit("sh3", "northwest", 0);
    add_exit("sh12", "southeast", 0);
    reset_domain_room();
}

