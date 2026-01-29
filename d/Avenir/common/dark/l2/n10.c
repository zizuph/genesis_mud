// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w4.c
// creator(s):       unknown
// revisions:        Casca, 11/13/99
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
    set_short("Stairs leading down");
    set_long("The tunnel comes to an abrupt end here. Very curiously "+
        "a set of ancient carved stairs leads down into the darkness.\n");

    add_exit(L4+"n25b", "down",0);
    add_exit("n9","south",0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item("stairs","The stairs lead downward into the darkness.\n");
    add_item(({"stair","stairs","stairway","stairwell"}),
        "A once majestic stairway has been carved from the "
        + "dark granite stone. Newels have been carved into "
        + "the shape of a serpent with the head at the top "
        + "and wings that sprout from its back are arched down "
        + "to reach the floor. The rest of the serpent "
        + "stretches downward into the darkness as the "
        + "handrails.\n");

    reset_tunnel_room();
}
