// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t44b.c
// creator(s):       Casca, 11/13/99
// revisions:   Lilith, Oct 2021: typo fixes
// purpose:         OPENING TO L4?
// note:           
// bug(s):
// to-do:

/* Inherit the room that is the base for the area. */
inherit "/d/Avenir/common/dark/darkl2_base.c";
inherit "/d/Avenir/inherit/sair_wall";

/* Include the local area defines, etc */
#include "/d/Avenir/common/dark/dark.h"  

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("dead end");
    set_long("A resonant whistling is omnipresent. It appears to be an "+
	    "effect caused by the wind passing through the odd tubular openings "+
		"lacing the walls. There isn't much room here, it is very tight "+
		"due to all the rubble and you are afraid it might collapse on "+
		"you if you stay much longer. A large rent piled with rubble in the "+
		"western wall could be the source of the wind, and a way out.\n");

    add_exit("t44", "out", 0, 0, 1);
    add_exit("t44", "rent", 0, 0, 1);
// This was never built
//    add_exit(L4b + "s11", "down",0,0,1);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"tubes","passages"}),"Small tube-like passages "+
        "line the walls. Some are too small to fit your smallest "+
        "finger into, while the largest would accept your whole "+
        "arm. Each size causes various frequency whistling sounds "+
        "as the wind passes through them.\n");
    add_item(({"wall","walls"}),"The walls contain hundreds of tubular "+
        "structures that whistle when the wind passes through them.\n");
    add_item("rent","A large rent in the "+
        "western wall is the source of the steady wind in this collapsed "+
        "tunnel. The rent is very large. It is choked full of large rubble, "+
        "it looks like this is the only way out of a dead-end.\n");

    add_tell("A high pitched whistle causes you to weep from the sound.\n");
    add_tell("A beautiful series of notes create a melody that would "+
        "cause virgins to weep.\n");
		
     set_sair_dest(({L2+"add/t36", L2+"add/t50", L2+"w6"}));
	 add_sair_wall();

    ::reset_tunnel_room();
}

public void
init()
{
    ::init();
    sair_init();  
}