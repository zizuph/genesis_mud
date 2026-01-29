// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s4.c
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
    set_short("Simple tunnel");
    set_long("This is a rather simple tunnel running from the northeast "+
        "to the southwest. The only feature of any interest is the manmade "+
        "tunnel that has been carved into the western wall.\n");

    add_exit("s3","northeast",0);
    add_exit("s5","southwest",0);
    add_exit("s6","west",0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_tell("You hear sounds of digging coming from the tunnel to the "+
        "west.\n");


    reset_tunnel_room();
}

