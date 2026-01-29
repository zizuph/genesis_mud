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
    try_item( ({ "narrow tunnel", "tunnel" }),
        "The tunnel becomes quite narrow here, almost a bit constraining. "
      + "The possibility of being trapped here is tangibly real.\n");     
    try_item( ({ "smell", "malodorous smell" }),
        "It smells like the rotting stench of death. Not being able to "
      + "place where it is coming from only increases the sense of "
      + "danger in this place.\n");
      
    add_exit(ROOMS + "tunnel03_07.c", "east");
    add_exit(ROOMS + "tunnel01_08.c", "southwest");

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
      + "cave system. The tunnel continues "+COMPOSITE_WORDS(exits)
      + ". The moss along the walls glow softly, illuminating your path. "
      + "There is a malodorous smell here but you can't really figure "
      + "out where it is coming from.\n";
    
    return desc;
}

