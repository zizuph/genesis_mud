// file name:        /d/Avenir/common/holm/shore/sh9.c
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
    set_short("Black sand beach");
    set_long("This is a narrow strand of black-sand beach, "+
        "swept by waves and wind alike. The stones of the "+
        "promontory loom in the east, extending farther out "+
        "to sea in the northeast. The obsidian wall which "+
        "protects the jungle beyond lies south, and gleams "+ 
        "like black glass in the diffuse light of the Source."+
        "\n");

    add_exit("sh10", "southeast", 0);
    add_exit("sh8", "northwest", 0);
    reset_domain_room();
}

