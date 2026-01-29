// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/s2.c
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
    set_short("Wide tunnel");
    set_long("The tunnel is rather wide here and it begins to angle "+
        "down towards the north. A grouping of rock columns adorns the "+
        "area near the east wall.\n");

    add_exit("s1","north",0);
    add_exit("s3","south",0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item(({"column","columns","pillar","pillars", "stalacmites", 
        "stalactites"}),
        "The moisture against the east wall has given birth "
        + "to stalactites and stalacmites that have grown "
        + "together to form solid columns of stone. They have "
        + "a soft brown coloring with grey striations.\n");
    add_item(({"east wall", "rivulets", "moisture"}),
        "Small rivulets of water snake down the east wall "
        + "creating small puddles in the rough floor along "
        + "its base.\n");
    add_item(({"puddles","puddle"}),
        "Small puddles have formed at the base of the east "
        + "wall.\n");


    reset_tunnel_room();
}
