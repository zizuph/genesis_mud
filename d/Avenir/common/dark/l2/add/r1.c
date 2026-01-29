// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/r1.c
// creator(s):       Casca, 11/13/99
// revisions:
// purpose:
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/albus_base.c";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_albus_room()
{
    set_short("Crude chamber");
    set_long("This is a small chamber carved from the wall of the "+
        "large chamber thats to the south. It appears to be used as a "+
        "storage room. Piles of furs and black powdery rocks are "+
        "scattered about and several broken crates litter the area.\n");


    add_exit("c1", "south");

    /*
     * Put additional add_items below. 
     */

    add_carved_room();
    add_item("crates","The broken remains of several crates that are "+
        "probably going to serve as firewood soon.\n");
    add_item(({"bedding","fur","furs"}),"Piles of fur lay about the "+
        "the cave.\n");
    add_item(({"rocks","coal","khoal"}),"These black powdery rocks are a "+
        "substance rather common in the black depths of the Utterdark. "+
        "Commonly called khoal, it is well known for its "+
        "flamability, producing a long-lasting and hot fire.\n");

    reset_albus_room();
}

