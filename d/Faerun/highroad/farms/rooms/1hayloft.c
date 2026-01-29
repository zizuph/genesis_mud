/*
 * Farmhouse kitchen
 * By Finwe, August 2006
 */
 
#pragma strict_types

#include "/d/Faerun/defs.h"
#include "defs.h"

inherit BASE_FARM;
inherit BASE_COMMON;

void
create_farm_room()
{
    iMaxEggs = 5;
    add_prop(OBJ_S_SEARCH_FUN, "do_search");

    set_short("A second level of the barn");
    set_long(short() + ". It fills the back half of the large barn. It is dusty with all the hay bales stacked up here. Light filters in between the cracks of the wall. A ladder leads down to the main level of the barn.\n");

    add_item(({"floor", "ground"}),
        "The floor is made of wide wood slats. They look well worn and full of bales of hay.\n");
    add_item(({"slats", "wide slats"}),
        "They are wide, smooth boards. Some are used as the floor, others as walls and the ceiling. They are weathered looking but still sturdy.\n");
    add_item(({"stalls"}),
        "They are down below in the main area of the barn. They look large and house animals.\n");
    add_item(({"ladder"}),
        "The ladder is large, and really resembles a large staircase. It is in the back of the barn and leads down to the main level of the barn. The ladder is wide and looks well used.\n");
    add_item(({"staircase", "stairs"}),
        "It is really a large ladder that resembles a staircase. The ladder is set in the back of the barn and leads down to the main level of the barn.\n");
    add_item(({"walls"}),
        "They are made of wood. They looks like they were once smooth, but have become rough in places over the years. There are cracks between the slats which filter light into the barn.\n");
    add_item(({"ceiling"}),
        "The ceiling is made of wood and look watertight. It comes to a peak and is just above you and is supported by many rafters.\n");
    add_item(({"rafters"}),
        "The rafters are a criss-cross lattice of beams made from large timers. They support the ceiling and look very sturdy.\n");
    add_item(({"hay", "bales of hay", "hay bales"}),
        "The hay is fresh and golden, and bundled in large bales. It is stacked against the wall and fills most of the second story. Some of the bales have been broken, leaving piles of fresh hay scattered around.\n");

    reset_room();
    set_add_chicken_noises();
    add_room_tell("A chicken flaps its wings and flies down below.");
    add_room_tell("A chicken flies up from below.");
    add_exit(FROOM_DIR + "1barn", "down");
    

}


void
reset_room()
{
    iEggFound = 0;
}
