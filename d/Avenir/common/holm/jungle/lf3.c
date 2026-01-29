// file name:        /d/Avenir/common/holm/jungle/lf3.c
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
    set_short("Following a narrow trail");
    set_long("This narrow trail is dappled by lacy leaf-shadows. "+
        "Tree limbs intertwine above, forming a green cathedral "+
        "canopy of breathtaking beauty. "+
        "The craggy stone underbelly of the island is exposed "+
        "here, eroded by water and cracked by roots. You can "+
        "hear the constant, gentle slapping of water against "+
        "a shore.\n");

    add_exit("lf4", "east", 0);
    add_exit("lf2", "west", 0);   

    add_item(({"west", "west trail", "west path"}),
       "This path leads west, toward the shore of the island. The "+
       "vegetation in this direction is thinner that to the east "+
       ".\n");  
    add_item(({"stone", "underbelly"}), "The stone is craggy and "+
       "dark, webbed by geometric cracks that bring to mind the "+
       "underbelly of a giant lizard.\n");

    add_cliff();
    add_seawall();
    add_fern();
    add_moss();
    add_atrack();

    reset_domain_room();
}

