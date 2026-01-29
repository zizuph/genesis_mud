// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t53.c
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
    set_short("gneiss cavern");
    set_long("This is a damp cavern with a large pool of water "+
        "along the southern edge. Three tunnels branch off "+
        "from here. There are footprints everywhere in the "+
		"gravel, especially near the water.\n");

    add_exit("t52", "west", 0);
	add_exit("t54", "northeast");
	add_exit("t57", "southeast");

    /*
     * Put additional add_items below. 
     */

    add_gneiss_tunnel();
	add_pool();

    ::reset_tunnel_room();
}

