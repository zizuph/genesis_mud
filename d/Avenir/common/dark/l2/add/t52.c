// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t52.c
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
void reset_tunnel_room(){ set_searched(0); ::reset_domain_room(); }

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Damp tunnel");
    set_long("This is a narrow damp tunnel that continues to the "+
        "to the southwest and the east. It appears to widen some "+
        "towards the east. You can see a glimmer of water to the "+
		"southwest.\n");

    add_exit("t51", "southwest",0);
    add_exit("t53", "east",0);

    /*
     * Put additional add_items below. 
     */

    add_gneiss_tunnel();
	add_item(({"water", "lake", "river"}), 
        "It's water. Its hard to tell more from here. You'll "+
        "have to figure out how to get closer if you want to "+
        "know more about it.");
    ::reset_tunnel_room();
}

