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
    set_area_type(5);
    add_exit(ROOMS + "tunnel04_03.c", "south");

    reset_room();
}

void
reset_room()
{
    if (random(4))
        clone_undead("skeleton", 80, 2, 4);
    if (random(4))
        clone_undead("ghoul", 130, 1, 2);
    if (random(4))
        clone_undead("devourer", 150, 1, 2);
}
