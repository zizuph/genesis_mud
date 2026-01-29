// file name:        /d/Avenir/common/holm/shore/sh22.c
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
    set_short("Rocky sea shore with crashing waves");
    set_long("You balance precariously on a rock with waves "+
        "crashing around you. The sounds of the water's rush and "+
        "thunder is almost deafening. A wind blows briskly from "+
        "the west, carrying upon it the salt-tang of the sea. "+
        "South, the rocks continue, while north is the safety "+
        "of the beach."+ 
        "\n");
    add_rocks();
    add_exit("sh20", "northeast", 0);
    add_exit("sh24", "south", 0);
    reset_domain_room();
}

