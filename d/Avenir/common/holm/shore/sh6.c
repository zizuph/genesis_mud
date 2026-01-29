// file name:        /d/Avenir/common/holm/shore/sh6.c
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
    set_long("You stand on a narrow promontory of rock "+
        "which extends defiantly into the restless sea. "+
        "The jagged edges of the stones upon which you "+
        "stand have been softened by centuries of endless "+
        "pounding surf. A west wind blows over you, car"+
        "rying odd sounds and the tangy, salt smell of "+
        "the sea.\n");

    add_exit("sh7", "southwest", 0);
    add_exit("sh5", "east", 0);

    set_up_herbs(({ ONEOF(beach), ONEOF(beach), ONEOF(beach) }), 
        ({ "shore", "sand", "beach", "grass" }), 5);
    set_up_herbs(({ ONEOF(sea), ONEOF(sea), ONEOF(sea) }), 
        ({ "sea", "water", "rocks", "seaweed", "flotsam", 
           "driftwood" }), 5);
    reset_domain_room();
}

