// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s3.c
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
    set_short("Fork in the passage");
    set_long("The tunnel forks here, going off"
	+" to the southwest and southeast, with the main tunnel"
	+" continuing to the north.\n");

    add_exit("s2","north",0);
    add_exit("s4","southwest",0);
    add_exit("s8","southeast",0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    reset_tunnel_room();
}
