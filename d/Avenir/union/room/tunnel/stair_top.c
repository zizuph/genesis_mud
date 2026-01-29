#pragma strict_types

#include "defs.h"
inherit SBASE;

public void
tunnel_room(void)
{
    ::tunnel_room();
    /*
     * This will be the master object for the cloned rooms which
     * a player will pass through on the way down.
     */
    link_master(STAIR_MASTER);

    add_exit("tunnel_landing", "up", 0, 2);
    add_exit("stair_bottom", "down", -8);
}
