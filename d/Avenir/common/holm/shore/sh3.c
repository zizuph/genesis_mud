// file name:        /d/Avenir/common/holm/shore/shore3.c
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
    set_short("Narrow beach along rocky shoreline");
    set_long("You stand on a narrow promontory of rock "+
        "which extends defiantly into the restless sea. "+
        "Jagged stones seem to have been stacked "+
        "haphazardly by the childish hand of a giant, "+
        "blocking your progress to the west. The action of "+
        "the waves seems particularly violent here, making "+ 
        "your footing a bit tenuous. A sea breeze whistles "+
        "over the stones, tickling your brow with tender "+
        "fingers.\n");
    add_rocks();
    add_exit("sh2", "southeast", 0);
    add_exit("sh4", "north", 0);
    reset_domain_room();
}

