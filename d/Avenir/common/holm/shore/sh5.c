// file name:        /d/Avenir/common/holm/shore/sh5.c
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
    set_short("Promontory, wild surf on rocky shoreline");
    set_long("Jumbled rocks, slick with water and algae, "+
        "mark the edge of the promontory. The surf crashes "+
        "with wild abandon against the unyielding stone, "+
        "spraying you with water. This place is desolate, "+
        "yet somehow throbbing with an intensity that makes "+
        "you feel vibrantly alive.\n");
    add_rocks();
    add_exit("sh4", "southeast", 0);
    add_exit("sh6", "west", 0);
    reset_domain_room();
}

