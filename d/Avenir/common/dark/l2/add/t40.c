// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t40.c
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

/* Now create the room.  */
void
create_tunnel_room()
{
    set_short("Whistling tunnel");
    set_long("A resonant whistling is omnipresent throughout this "+
        "tunnel. It appears to be an effect caused by the walls "+
        "which are laced with odd tubular passages that cause "+
        "various frequency whistles as the nearly steady wind "+
        "blows through here.\n");

    add_exit("t39", "west", 0);
    add_exit("t41", "east", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"tubes","passages"}),"Small tubelike passages "+
        "line the walls. Some are too small to fit your smallest "+
        "finger into, while the largest would accept your whole "+
        "arm. Each size causes various frequency whistling sounds "+
        "as the wind passes through them.\n");
    add_item(({"wall","walls"}),"The walls contain hundreds of tubular "+
        "structures that whistle when the wind passes through them.\n");
    add_tell("A high-pitched whistle causes you to wince from the sound.\n");
    add_tell("A beautiful series of notes create a melody that would "+
        "cause virgins to weep.\n");

    reset_tunnel_room();
}

