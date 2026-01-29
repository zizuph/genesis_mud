// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t1.c
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
    set_short("A new tunnel");
    set_long("This is a recently carved tunnel created to link two natural "+
        "galleries together. "+
        "Debris from the construction still litters the floor in places. "+
        "To the west is the end of the new section and the begining of a "+
        "natural tunnel.\n");

    add_exit("t2", "east", 0);
    add_exit(L2 +"s11", "west", 0); 



    /*
     * Put additional add_items below. 
     */

    add_r_tunnel();


    add_item(({"debris","litter","rocks","dust"}),
        "Rocks and dust litter the floor.  Most of it has been "+
        "pushed back towards the walls by the feet of those "+
        "who have passed by.\n");

    reset_tunnel_room();
}

