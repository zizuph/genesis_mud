// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t48.c
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
    set_short("Ledge");
    set_long("This is a wide ledge hanging above a raging subterranian "+
        "river. The river flows from the north to the south in a wide "+
        "passage that it has carved over the ages. A rope bridge has "+
        "been suspended over the river to the east. A tunnel goes off "+
        "to the southwest.\n");

    add_exit("t47", "east","@@bridge@@");
    add_exit("t50", "southwest", 0);

    /*
     * Put additional add_items below. 
     */

    add_n_tunnel();

    add_item("bridge","A rickety, none too steady rope bridge with wooden "+
        "planking has been anchored to the ledge here and to a ledge "+
        "on the far side of the river. The ropes and the wood have taken "+
        "much abuse from the moisture in the air, you wonder at its "+
        "security.\n");
    add_item("river","A raging river flows no more than ten feet below "+
        "you.\n");

    reset_tunnel_room();
}

mixed
bridge()
{
    write("You slowly work your way across the bridge.\n It "+
        "creaks and sways beneath you ominously.\n");
    say(QCTNAME(TP) + " slowly crosses the bridge.\n");
    return 0;
}

