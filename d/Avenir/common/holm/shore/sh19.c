// file name:        /d/Avenir/common/holm/shore/sh19.c
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
    set_short("Stretch of black sand, sheltered from the waves");
    set_long("A wide stretch of beach sheltered north and south "+
        "by large collections of boulders, it abuts the obsidian "+
        "seawall east of here. Little humps of seaweed have washed "+
        "high up on the shore, looking dry and bedraggled. Waves "+
        "crash against the rocks offshore, flinging saltspray and "+ 
        "thunder into the air."+
        "\n");
    add_beachs();
    add_flotsam();
    add_grass();
    add_rocks();
    add_exit("sh17", "north", 0);
    add_exit("sh18", "west", 0);
    add_exit("sh21", "south", 0);
    add_exit("sh20", "southwest", 0);
    reset_domain_room();
}

