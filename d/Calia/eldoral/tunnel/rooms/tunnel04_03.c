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
    set_area_type(1);

    add_exit(ROOMS + "tunnel04_02.c", "north");
    add_exit(ROOMS + "tunnel04_04.c", "south");
    add_exit(ROOMS + "tunnel05_02.c", "northeast");

    reset_room();
}

void
reset_room()
{
    object cat;
    int i;
    
    for (i = 0; i < 2; i++)
    {
		if (sizeof(filter(all_inventory(TO), &->id("undead"))) > 2)
			continue;

        cat = clone_object(TUN_NPCS+"ghost_cat");
        cat->move(TO);
    }
    
    if (random(4))
        clone_undead("skeleton", 60, 2, 4);
}
