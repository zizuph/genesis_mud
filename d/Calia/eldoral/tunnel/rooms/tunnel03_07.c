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
        "The tunnel is quite narrow here and it's quite difficult to "
      + "prevent yourself from not stepping on the crunchy bones "
      + "beneath your feet.\n");
    
    try_item( ({ "skeletons", "bones", "old skeletons", "old bones",
                 "remains", "old remains" }),
        "Scattered across the ground are the old remains of long-forgotten "
      + "warriors. As you step on them, you hear soft cracks and crunches.\n");
    
    try_item( ({ "moan", "low moan" }),
        "A low moan seems to come from the west exit. Due to the echoes "
      + "in these caves, it is hard to tell for sure. It's a low gutteral "
      + "type chills you to your bone.\n");
    
    try_item( ({ "tunnel system", "cave system", "system" }),
        "The cavernous tunnel system stretches quite far, from what you "
      + "can tell. You cannot make out much beyond the current location "
      + "though as it is quite dark.\n");
    
    add_exit(ROOMS + "tunnel02_07.c",  "west");
    add_exit(ROOMS + "tunnel04_07.c",  "east");

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
    return "In a narrow tunnel";
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
    desc = "You find yourself stopped in a narrow tunnel of a rather "
        + "large tunnel system. It continues " + COMPOSITE_WORDS(exits)
        + ". Along the sides of the narrow pathway, old skeletons and "
        + "bones are scattered. You hear a low moan and you think it "
        + "may be coming from the southeast.\n";
    return desc;
}
