// file name:        /d/Avenir/common/holm/shore/sh21.c
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
    set_short("Stretch of black sand");
    set_long("This is a lovely stretch of black sand beach, "+
        "smoothed by tide and wind to a near perfect plane. "+
        "A seawall rises in the east, protecting the jungle "+
        "beyond. The promontory looms in the north, looking "+
        "like a prehistoric leviathan collapsed on the shore. "+ 
        "A large collection of boulders lies southwest."+
        "\n");
    add_beachs();
    add_rocks();
    add_exit("sh19", "north", 0);
    add_exit("sh20", "west", 0);
    add_exit("sh23", "southeast", 0);
    add_exit("sh18", "northwest", 0);
    reset_domain_room();
}

