/*
 * Eldoral Undead Tunnel Underground
 *
 * Created by Petros, November 2008
 */
 
#include <composite.h>
#include "defs.h"

inherit UNDERGROUND_BASE;

public void
create_tunnel_room()
{
    setuid();
    seteuid(getuid());
    
    // All exits in the underground are handled by the
    // EXIT_HANDLER. The handler has the array of all the edges
    // that connect the rooms together. To add a new exit(edge),
    // please add it to the EXIT_HANDLER and not here.
    EXIT_HANDLER->load_exits(this_object());

    add_object(TUN_DOORS + "gate1_inside");

    reset_room();
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
    return "Underground room";
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
    desc = "You have arrived in a nondescript room that leads out to "
        + "the " + COMPOSITE_WORDS(exits) + ".\n";

    return desc;
}
