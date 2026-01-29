// file name:        /d/Avenir/common/holm/shore/sh4.c
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
    set_short("Promontory, rocky shoreline");
    set_long("There is nothing but stone here and the "+
        "violence of the waves tugging at your feet. The "+
        "dark sea, pregnant with mystery, seems to speak "+
        "to you in a wordless, enticing voice. A strong "+
        "breeze blows over you, sprinkling your skin with "+ 
        "salt-spray.\n");

    add_exit("sh3", "south", 0);
    add_exit("sh5", "northwest", 0);
    reset_domain_room();
}

