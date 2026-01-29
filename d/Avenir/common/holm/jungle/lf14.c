// file name:        /d/Avenir/common/holm/jungle/lf14.c
// creator(s):       Lilith, Nov 96
// revisions:
// purpose:
// note:
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/holm/jungle/jungle_base";

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
create_jungle_room()
{
    set_short("lowland forest on the Holm");
    set_long("You are in the humid embrace of a lowland forest. "+
        "All around is a forest of mossy limbs, every tree "+
        "branch draped with moss like green wool hung out to "+
        "dry. The soughing of the wind makes the mist collect"+
        "ing around your ankles swirl as though the forest it"+
        "self breathes. A jagged obsidian wall blocks the view "+
        "of the sea to the west, but you can still hear the lapping "+
        "of the surf against the shore.\n");

    add_seawall();
    add_fern();
    add_moss();
    add_atrack();

    add_exit("lf12", "north", 0);
    add_exit("lf18", "south", 0);

    reset_domain_room();
}
