// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t36.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Center");
    set_long("You are in the center of a large circular cavern. "+
        "The cavern itself is natural but the floor here in the "+
        "middle has been smoothed and lowered towards the center "+
        "in concentric rings. At the heart of the rings is a "+
        "large pillar of stone that seems to pierce both "+
        "the floor and ceiling.\n");

    add_exit("t33", "south");
    add_exit("t34", "west");
    add_exit("t35", "east");
    add_exit("t37", "north");


    /*
     * Put additional add_items below. 
     */

    add_cavern();

    add_item("pillar","The pillar is so massive it would take nearly "+
        "six large men linking hands to encircle it. Its entire "+
        "surface has been engraved with symbols and runes that have "+
        "been nearly removed by the passage of time. At seemingly "+
        "random intervals cylindrical holes penetrate into the "+
        "pillar to an unknown depth.\n");
    add_item(({"rings","circles","steps"}),"The floor has been carved "+
        "with steps that radiate out from the pillar in concentric "+
        "circles.\n");
    add_item(({"symbols","runes"}),"Symbols and runes have been "+
        "engraved in to the surface of the pillar but they have been "+
        "worn to the point of illegibility by time.\n");
    add_item(({"holes", "hole"}), 
	    "Cylindrical holes penetrate the pillar at various "+
        "places and levels. You can not tell how deep the holes go "+
        "into the pillar.\n");
    add_prop(OBJ_S_SEARCH_FUN, "search_dark");
    reset_tunnel_room();
}

