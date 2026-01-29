// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t49.c
// creator(s):       Casca, 11/13/99
// revisions:        removed by Lilith it didn't fit map
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
    set_short("Damp tunnel");
    set_long("The tunnel here is slick with dampness.  "+
       "You can hear a roaring sound to the northeast. "+
       "The tunnel also goes off to the west.\n");

//    add_exit("t48", "northeast", 0);
//    add_exit("t50", "west", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}

