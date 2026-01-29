// file name:        /d/Avenir/common/holm/shore/sh24.c
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
    set_short("Wave-swept rocky shoreline");
    set_long("You stand above the reach of the waves, on a large "+
        "stone slippery with algae. The sea slaps and hisses below "+
        "you, sending salt-spray into the air. The looming stones "+
        "of the promontory extend northwest into the sea, while "+
        "east you can see the tops of trees extending above the "+
        "obsidian seawall. A broad, dry ledge can seen southeast "+ 
        "of here."+
        "\n");
    add_rocks();
    add_exit("sh22", "north", 0);
    add_exit("sh26", "southeast", 0);
    reset_domain_room();
}

