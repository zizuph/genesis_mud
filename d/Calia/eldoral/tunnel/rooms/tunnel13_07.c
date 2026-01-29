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
    set_area_type(4);

    add_exit(ROOMS + "tunnel14_07.c",  "east");
    add_exit(ROOMS + "tunnel12_08.c", "southwest");

    reset_room();
}

void
reset_room()
{
    if (random(4))
        clone_undead("skeleton", 60, 2, 4);
}
