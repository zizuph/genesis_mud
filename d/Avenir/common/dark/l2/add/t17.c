// -*-C++-*-
// file name:        /d/Avenir/common/dark/l2/t17.c
// creator(s):       Casca, 11/13/99
// revisions:   Lilith, Nov 2021 adding gneiss gnomes
// purpose:
// note:          This was the blue barrier room.
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
    set_short("eastern gneiss tunnel");
    set_long("This tunnel runs from southwest to north. "+
        "It appears to be used occasionally judging by the wear "+
        "on the floor. There is a breeze blowing from the "+
        "north, carring a faint whistling sound. The ceiling "+
        "is rather low here, making you feel a bit nervous.\n");

    add_exit("t16", "southwest", 0);
	add_exit("t56", "north", 0);
//    add_exit("t18", "north", "@@do_pass@@");

    /*
     * Put additional add_items below. 
     */

    add_gneiss_tunnel();
/*
    add_item(({"barrier","blue barrier","shimmering blue barrier"}),
        "A shimmering blue barrier that hums with energy has "+
        "been set across the tunnel to the north.\n");
*/
    reset_tunnel_room();
}


int 
do_pass()
{

    if (TP->query_wiz_level())
    {
        write("You step through the shimmering blue barrier.\n");
        return 0; 
    }

    else
    {
        write("You attempt to step through the shimmering blue "+
            "barrier, but as your body comes in contact with it you "+
            "are stopped dead in your tracks.\n");
        say(QCTNAME(this_player())+ " walks up to the shimmering "+
            "blue barrier, but then stops dead right before crossing "+
            "through it.\n");
        return 1;  
    }
  return 0;
}

