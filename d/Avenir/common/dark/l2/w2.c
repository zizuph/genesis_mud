// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w2.c
// creator(s):       unknown
// revisions:        Casca, 11/21/99
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
    set_short("Long cavern");
    set_long("You are standing in the south end of a long cavern. It "+
        "extends to the north while a smaller tunnel goes northeast. "+
        "The ceiling has a high natural vault with hundreds of small "+
        "stalactites which capture light and reflect it back. The floor "+
        "is so covered with stalagmites that its hard to walk through "+
        "here.\n");

    add_exit("w3","northwest",0);
    add_exit("w1","southeast",0);


    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
    add_item(({"ceiling","roof","above","stalactites"}),
        "The ceiling is nearly covered with small "
        + "stalactites. Many of them contain pieces of small "
        + "crystal that reflect the light.\n");
    add_item("crystals",
        "The crystals in the stalactites catch the light in "
        + "the room and reflect it back, creating a beautiful "
        + "effect that strikes wonder into your heart.\n");
    add_item(({"floor","ground"}),
        "The floor is covered with small stalacmites. They "
        + "are so plentiful that they make walking difficult.\n");
}

