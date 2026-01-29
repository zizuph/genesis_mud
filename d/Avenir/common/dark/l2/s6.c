// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s6.c
// creator(s):       unknown
// revisions:        Casca, 11/18/99
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
    set_short("New tunnel");
    set_long("This is a rather recently excavated tunnel. Even though "+
         "its new the tunnel has been cleaned of all the debris cause "+
         "by its constuction.\n");

add_exit("s4","east",0);
add_exit("s7","northwest",0);


    /*
     * Put additional add_items below. 
     */

    add_r_tunnel();
    add_new_tunnel();

    reset_tunnel_room();
}