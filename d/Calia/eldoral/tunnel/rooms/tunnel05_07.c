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
    set_area_type(2);

    add_exit(ROOMS + "tunnel04_07.c",  "west");
    add_exit(ROOMS + "tunnel06_08.c", "southeast");

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
