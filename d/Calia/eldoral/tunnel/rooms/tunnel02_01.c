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
    try_item( ({ "corpses", "figures", "humanoid figures" }),
        "The corpses are all decaying humanoid figures "
      + "set into a position as though they are praying.\n");
    
    try_item( ({ "walls", "wall" }),
        "Corpses line the walls of this dead end. Fortunately for you "
      + "the corpses do not look fresh.\n");
    
    try_item( ({ "positions", "position" }),
        "Only one with a depraved mind would think to place the "
      + "humanoid figures in these positions. Though kneeling in "
      + "prayer is usually a peaceful pose, the corpses look like "
      + "they are suffering.\n");
    
    try_item( ({ "chapel", "ruins", "temple", "stone",
                "scattered stones", "broken stones", "rubble",
                "old temple" }),
        "What was probably a glorious temple is now in ruins, lying "
      + "in heaps of stone rubble. The sheer amount of rock prevents "
      + "you from entering it. Not that you would want to.\n");
      
    add_exit(ROOMS + "tunnel03_02.c", "southeast");
    
    reset_room();

}

void
reset_room()
{
    if (random(4))    
        clone_undead("heucuva", 120, 6, 6);

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
    return "Ruined temple";
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
    desc = "You have arrived at a dead end. The only way out of here "
      + "is to the " + COMPOSITE_WORDS(exits) + ". There are many corpses "
      + "lining the walls, set into positions resembling those praying "
      + "in a chapel. Scattered and broken stones lie around the ruins "
      + "of what appears to be a grotesque mockery of an old temple.\n";
    
    return desc;
}

