// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t2.c
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
    set_long("This is a recently-carved tunnel, created to link two natural "+
        "galleries together. Debris from the construction still litters the "+
        "floor in places. A natural tunnel is to the east while the newly "+
        "constructed tunnel extends further west.\n");


    add_exit("t1", "west", 0);
    add_exit("t3", "east", 0);


    /*
     * Put additional add_items below. 
     */

    add_r_tunnel();
    add_new_tunnel();

    add_item(({"debris","litter","rocks","dust"}),
        "Rocks and dust litter the floor.  Most of it has been "+
        "pushed back towards the walls by the feet of those "+
        "who have passed by.\n");

    reset_tunnel_room();
}

