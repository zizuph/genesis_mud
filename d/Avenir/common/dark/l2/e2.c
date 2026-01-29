// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/e2.c
// creator(s):       Tepisch, longtimeago
// revisions:        Casca, 11/25/99
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
    set_short("Narrow tunnel");
    set_long("This long tunnel narrows to the south. The tunnel "+
        "seems rather frequently used and kept in a tidy manner. "+
        "You notice light and smoke from the tunnel to the south.\n");

    add_exit("e1","northwest");
    add_exit("e3","south");


    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item("light",
        "Towards the south you see a dim light filling the "+
        "tunnel.\n");
    add_item("smoke",
        "A light haze of smoke flows through this tunnel "+
        "towards the northwest.\n");

    reset_tunnel_room();
}
