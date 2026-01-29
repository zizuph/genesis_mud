// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t44.c
// creator(s):       Casca, 11/13/99
// revisions:   Lilith, Oct 2021: typo fixes
// purpose:         OPENING TO L4?
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
    set_short("Whistling tunnel");
    set_long("A resonant whistling is omnipresent throughout this "+
        "tunnel. It appears to be an effect caused by the wind passing "+
        "through the odd tubular openings lacing the tunnel walls. A "+
        "large rent in the floor near the "+
        "eastern wall appears to be the source of the wind.\n");

    add_exit("t43", "west");
// This was never built
//    add_exit(L4b + "s11", "down",0,0,1);

    /*
     * Put additional add_items below. 
     */
    add_prop("_av_mine_special", 1);
    add_n_tunnel();

    add_item(({"tubes","passages"}),"Small tube-like passages "+
        "line the walls. Some are too small to fit your smallest "+
        "finger into, while the largest would accept your whole "+
        "arm. Each size causes various frequency whistling sounds "+
        "as the wind passes through them.\n");
    add_item(({"wall","walls"}),"The walls contain hundreds of tubular "+
        "structures that whistle when the wind passes through them.\n");
    add_item("rent","A large rent in the floor at the base of the "+
        "eastern wall is the source of the steady wind in this tunnel. "+
        "The rent is very large. It is choked full of large rubble, "+
        "it looks like this is a dead-end.\n");

/*                               You could possibly go down to a deeper "+
        "section of tunnels from here.\n");
*/
    add_tell("A high pitched whistle causes you to weep from the sound.\n");
    add_tell("A beautiful series of notes create a melody that would "+
        "cause virgins to weep.\n");

    reset_tunnel_room();
}

