// file name:        /d/Avenir/common/holm/shore/sh15.c
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
    set_short("Black sand beach sheltered from the waves");
    set_long("A sheltered corner of the beach, protected from "+
        "waves by a collection of large boulders southwest. "+
        "The sand here is the consistency of cornmeal, and it "+
        "glitters in the diffuse light of the Source. The "+
        "obsidian seawall is directly to the east, and beyond "+ 
        "it you can hear the cries of jungle animals."+
        "\n");
    add_beachs();
    add_rocks();
    add_exit("sh14", "west", 0);
    add_exit("sh17", "south", 0);
    reset_domain_room();
}

