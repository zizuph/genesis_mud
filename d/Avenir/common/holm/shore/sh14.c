// file name:        /d/Avenir/common/holm/shore/sh14.c
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
    set_long("Off-shore, the waves thunder against numerous "+
        "rocks projecting up from the seafloor. Here, the "+
        "beach is made of black sand, soft and powdery under"+
        "foot, but it gives way rather abruptly to a collection "+
        "of boulders and tide pools in the southwest. The "+
        "obsidian seawall rises in your east, "+
        "obscuring the sight of the jungle beyond, but not "+ 
        "the sounds."+
        "\n");
    add_beachs();
    add_rocks();
    add_exit("sh13", "northeast", 0);
    add_exit("sh15", "east", 0);
    add_exit("sh16", "southwest", 0);
    reset_domain_room();
}

