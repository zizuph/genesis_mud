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
    try_item( ({ "stream", "streams", "puddle", "pool", "water",
                 "shallow pool", "small streams"}),
        "Small streams of water run down the walls, forming a small, "
      + "shallow pool of water on the ground. Some of the water "
      + "flows south of here.\n");
    try_item( ({ "wall", "walls" }),
        "Besides the water running down the walls, there is a significant "
      + "amount of moss growing upon it.\n");
    try_item( ({ "glow", "rainbow", "rainbow pattern", "pattern" }),
        "The patterns shift and change according to the flow and movement "
      + "of the water.\n");
      
    add_exit(ROOMS + "tunnel02_01.c", "northwest");
    add_exit(ROOMS + "tunnel03_03.c", "south");

    reset_room();
}

void
reset_room()
{
    if (random(4))
        clone_undead("skeleton", 60, 2, 4);
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
    return "A bend in the tunnel";
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
    desc = "You and standing in the middle of a sharp bend in the tunnel. "
      + "It leads "+COMPOSITE_WORDS(exits)+ ". A soft glow illuminates the "
      + "tunnel and it seems to be coming from the moss on the walls. "
      + "Small streams of water run down the walls, forming a puddle on "
      + "the ground. The light from the moss is refracted through the "
      + "water to create a rather pleasant rainbow pattern.\n";
    
    return desc;
}

