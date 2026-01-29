// file name:        /d/Avenir/common/holm/shore/sh23.c
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
    set_short("Sandy path, sheltered from the waves");
    set_long("A narrow, sandy path, sheltered from the violence "+
        "of the sea by a pile of rocks west of you. The sand is "+
        "dark and very dry, making it powdery underfoot. The jungle "+
        "grows very near the seawall here, you can see the tops of "+
        "some towering treeferns. You can just see the northern tip "+
        "of the promontory extending into the sea."+
        "\n");
    add_beachs();
    add_rocks();
    add_salt();
    add_exit("sh21", "northwest", 0);
    add_exit("sh25", "south", 0);
    add_exit("sh27", "east", 0);
    reset_domain_room();
}

