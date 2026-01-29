// file name:        /d/Avenir/common/holm/shore/sh7.c
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
    set_short("Promontory, surf-swept rocky shoreline");
    set_long("The stones of the promontory gleam darkly "+
        "in the diffuse light, looming like a leviathan "+
        "emerging from the jealous sea. Waves sweep the "+
        "gravelly shore, leaving bits of flotsam and "+
        "seaweed in their wake. A dead tree, stripped of "+
        "bark and silvered with age, stares out to sea, "+
        "its limbs bent in supplication.\n");
    add_item(({"tree", "dead tree"}), "This tree has been "+
        "long dead. Weathered by wind and water, it is hard "+
        "and unyielding as the stone from which it grew.\n");
    add_cmd_item(({"tree", "dead tree"}), "climb", 
        "The tree is too smooth, and its branches too high, "+
        "for you to climb up into it.\n");
    add_beachg();
    add_flotsam();
    add_exit("sh8", "southeast", 0);
    add_exit("sh6", "northeast", 0);
    reset_domain_room();
}

