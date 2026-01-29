// file name:        /d/Avenir/common/holm/shore/sh25.c
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
    set_short("Narrow stretch of black sand, sheltered from the waves");
    set_long("This is a narrow stretch of black sand, forming a path "+
        "of sorts that runs between the obsidian seawall and the pile "+
        "of rocks and boulders against which the sea pounds. It is "+
        "lined with tufts and small hillocks of beach grass. Above "+
        "and to the southwest is a ledge which overhangs the violent"+
        "ly thrashing sea."+ 
        "\n");
    add_beachs();
    add_grass();
    add_rocks();
    add_exit("sh23", "north", 0);
    add_exit("sh27", "northeast", 0);
    add_exit("sh26", "up", 0);
    reset_domain_room();
}

