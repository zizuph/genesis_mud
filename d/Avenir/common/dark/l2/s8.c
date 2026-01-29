// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s8.c
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
    set_short("Plain tunnel");
    set_long("The passageway heads from northwest"+
	" to southeast. There is little of distinction here,"+
    " except that there is a narrow set of stairs leading down."+
    " South and east of this point, the way seems to grow dusty.\n");

add_exit("s3","northwest",0);
add_exit("s9","southeast",0);
add_exit(L3 + "s5_l2","down",0);


    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"dust"}),"The tunnel to the southeast is obscured by a "+
        "cloud of dust.\n");


    reset_tunnel_room();
}
