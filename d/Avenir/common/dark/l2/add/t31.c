// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t31.c
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
    set_short("Tunnel");
    set_long("The mouth of a shadow-shrouded cavern lies north.  "+
        "Something flickers from within, casting eerie shards of "+
       "light that fail to pierce the shadows. This short tunnel "+
       "connects with another one to the northeast.\n");

     add_exit("t7", "northeast");
     add_exit("c1", "southwest",); 


    /*
     * Put additional add_items below. 
     */

   add_n_tunnel();

    reset_tunnel_room();
}

