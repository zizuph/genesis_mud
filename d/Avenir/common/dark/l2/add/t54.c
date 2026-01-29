// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t
// creator(s):       Lilith Nov 2021
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
    add_gneiss_tunnel();

    set_short("north gneiss tunnel");
    set_long("This is a gneiss tunnel with a gravel floor. There "
        +"is a small fissure in the tunnel wall, and you think you "
        +"can hear an occasional screech and fluttering noises "
        +"coming from it. A pervasive stench makes your eyes water. "
        +"A strong wind and eerie tones come "
        +"from the north. You can feel gravel grinding under your "
        +"feet.\n");
    
    add_exit("t42", "north",0);
    add_exit("t53", "southwest",0);
	add_exit("t54b", "fissure", 0,0,1); // non-obvious
	add_exit("t54b", "enter", 0,0,1); // non-obvious
	
    /*
     * Put additional add_items below. 
     */

    add_item(({"fissure", "small fissure"}),
        "This is a small fissure. It might be big enough to "+
        "squeeze into, but by the sound of it, there are "+
		"bats living there.\n");		


    ::reset_tunnel_room();
}

