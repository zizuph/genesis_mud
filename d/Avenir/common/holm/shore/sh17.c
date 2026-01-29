// file name:        /d/Avenir/common/holm/shore/sh17.c
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
    set_long("The sand underfoot is the consistency of cornmeal, "+
        "and it glitters in the diffuse light of the source. A "+
        "large pile of boulders due west prevents the waves from "+
        "reaching here. A sea breeze whistles over the stones, "+
        "tickling your brow with tender fingers. The seawall "+
        "lies east, and a promontory juts out into the sea "+ 
        "farther north."+
        "\n");
    add_beachs();
    add_rocks();

    add_exit("sh15", "north", 0);
    add_exit("sh19", "south", 0);
    reset_domain_room();
}

