/*
 * Eldoral Undead Tunnels
 *
 * Originally coded by Jaacar (Mike Phipps), October 2003
 * Adapted by Petros, November 2008
 */
 
#include <composite.h>
#include "defs.h"
inherit UNDERGROUND_BASE;

#define COORDX 6
#define COORDY 8


void
create_tunnel_room()
{
    set_area_type(1);

    add_exit(ROOMS + "tunnel05_07.c", "northwest");
    add_exit(ROOMS + "tunnel06_07.c", "north");
    add_exit(ROOMS + "tunnel07_08.c",  "east");
    add_exit(ROOMS + "tunnel07_07.c", "northeast");

    reset_room();
}

void
reset_room()
{
    object cat;
    int i;
    
    for (i = 0; i < 2; i++)
    {
		if (sizeof(filter(all_inventory(TO), &->id("ghost cat"))) > 2)
			continue;

        cat = clone_object(TUN_NPCS+"ghost_cat");
        cat->move(TO);
    }
    
    if (random(4))
        clone_undead("skeleton", 60, 2, 4);
    if (random(8))
        clone_undead("wraith", 150, 1, 2);
}
