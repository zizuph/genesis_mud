// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w3.c
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
    set_long("This is a place to strike wonder into even the hardest "+
        "heart.  The ceiling has a high natural vault with hundreds "+
        "of small stalactites.  Water drips from straw-like mineral "+ 
        "formations onto the stalacmite-studded floor. "+
        "Many of the stalacmites have been removed and others are in "+
        "various stages of demolition. It appears that "+
        "someone is in the process of converting this place into "+
        "something more useful.\n");


    add_exit("w2","southeast",0);
    add_exit("w4","north",0);


    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
    add_item(({"ceiling","roof","above","stalactites"}),
        "The ceiling is nearly covered with small "
        + "stalactites. Many of them contain pieces of small "
        + "crystal that reflect the light.\n");
    add_item(({"floor","ground"}),
        "The floor here was once covered with stalagmites "
        + "but someone has been working to remove them. Most "
        + "of the floor is now level with the stalacmites "
        + "having been removed. The rest are in various "
        + "stages of destruction.\n");
    add_item("stalacmites",
        "The few stalacmites that remain are in the process "
        + "of being removed. Most are just stubs of what they "
        + "once where and bare scars from chisel and pickaxe.\n");
    add_item("crystals",
        "The crystals in the stalactites catch the light in "
        + "the room and reflect it back.\n");
}
