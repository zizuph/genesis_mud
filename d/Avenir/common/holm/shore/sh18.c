// file name:        /d/Avenir/common/holm/shore/sh18.c
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
    set_short("Wave-swept rocky shoreline");
    set_long("A stretch of black sand beach, swept by waves. "+
        "The sand here is very fine, and dried salt stains it "+
        "with wavy white lines, marking the ebb and flow of the "+
        "tide. The stones of the promontory rise in the north, "+
        "beyond the collection of boulders and tidepools stand"+
        "ing between the violence of the sea and the glossy "+ 
        "stone of the obsidian seawall."+
        "\n");
    add_beachs();
    add_rocks();
    add_salt();
    add_exit("sh16", "northwest", 0);
    add_exit("sh19", "east", 0);
    add_exit("sh20", "south", 0);
    add_exit("sh21", "southeast", 0);
    reset_domain_room();
}

