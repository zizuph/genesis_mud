// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/w6.c
// creator(s):       unknown
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
    set_short("Windy tunnel");
    set_long("The passage turns here, heading from the southeast "+
        "to the north. "+
        "The edges of a jagged rent in the west wall are covered "+
        "in dust, while the rest of the tunnel is surprisingly "+
        "dust-free. "+
        "A fair wind blows past you in the direction of the hole.\n");

    add_exit("w5","south");
    add_exit("w7","north");
    add_exit(L1 + "stair1.c", "west");

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"rent", "hole", "west wall", "wall"}),
        "The west wall, dark and lined with faint mineral veins, "+
        "looks as if giant hands ripped a hole in it. You cannot "+
        "see inside the rent. Perhaps you should try going west?\n");
    add_item(({"dust", "edge", "edges"}),
        "The dust is very fine and of a lighter colour than the walls. "+
        "It seems to be sticking to the rough edges of the rent, "+
        "probably blown there by the wind.\n");
    add_tell("The wind whistles through the rent in the west wall.");

    reset_tunnel_room();
}
