/*
 * Eldoral Undead Tunnels
 *
 * Originally coded by Jaacar (Mike Phipps), October 2003
 * Adapted by Petros, November 2008
 */
 
#include <composite.h>
#include "defs.h"

inherit UNDERGROUND_BASE;

public void
create_tunnel_room()
{
    try_item( ({ "dead end", "end" }),
        "The tunnel ends quickly here. Whoever dug this tunnel must have "
      + "stopped for some reason. Piles of bones lie deep in the dark "
      + "recesses of this area.\n");
    try_item( ({ "bones", "piles", "pile", "bone", "piles of bones" }),
        "Some of the bones appear to be from humanoid sources. They "
      + "appear to be rather old and tattered. There doesn't appear "
      + "to be much else other than the cleanly picked bones.\n");
    
    add_exit(ROOMS + "tunnel02_07.c", "northeast");
    reset_room();
}

void
reset_room()
{
    if (random(4))
        clone_undead("skeleton", 60, 3, 4);
    if (random(4))
        clone_undead("ghoul", 130, 1, 2);
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
    return "Dead end";
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
    desc = "You have arrived at a dead end. The tunnel narrows quickly "
        + "into the end. The only way out of here is to the " 
        + COMPOSITE_WORDS(exits) + ". Piles of bones lie on the ground. "
        + "In relief, you notice that they don't seem to be fresh.\n";
    
    return desc;
}

