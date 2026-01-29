/*
 * Eldoral Undead Tunnels
 *
 * Originally coded by Jaacar (Mike Phipps), October 2003
 * Adapted by Petros, November 2008
 */
 
#include <composite.h>
#include "defs.h"
inherit UNDERGROUND_BASE;

void
create_tunnel_room()
{
    try_item( ({ "ground", "water" }),
        "The ground is wet enough to reflect the light off the walls. You "
      + "follow a stream with your eyes and note that it is coming from "
      + "the north.\n");
      
    add_exit(ROOMS + "tunnel03_02.c", "north");
    add_exit(ROOMS + "tunnel03_04.c", "south");

    reset_room();
}

void
reset_room()
{
    if (random(4))
        clone_undead("skeleton", 60, 2, 4);
    if (random(4))
        clone_undead("zombie", 120, 2, 4);
}


/*
 * Function     : query_tunnel_short
 * Description  : Returns the short description for this particular
 *                room.
 * Arguments    : none
 * Returns      : short description
 */
public string
query_tunnel_short()
{
    return "Along a narrow tunnel";
}

/*
 * Function     : query_tunnel_long
 * Description  : Returns the long description for this particular
 *                room.
 * Arguments    : none
 * Returns      : long description
 */
public string
query_tunnel_long()
{
    string * exits;
    string desc;
    
    exits = query_obvious_exits();
    desc = "You are venturing along a narrow tunnel inside a big "
      + "cave system. The tunnel continues " + COMPOSITE_WORDS(exits)
      + ". The cave walls are covered with a dark-green, slimy moss. "
      + "There is a malodorous smell here but you can't really figure "
      + "out where it is coming from. You can see that the ground is "
      + "wet as it reflects the light coming from the moss. The water "
      + "seems to be coming from the north.\n";
    
    return desc;
}

