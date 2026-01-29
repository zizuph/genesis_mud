/* Corridor-Stairs (5).
 * Coded by Marisol (09/28/98)
 * Copyright (c) Marisol Ramos 1998
 */


#pragma strict_types
#include "defs.h"
inherit CASTLE_OV2;


void
create_castle_room()
{

    set_short("A staircase to the third floor");
    set_long("An old staircase rise up to the third floor. This "+
        "room is almost bare. The staircase doesn't look in better "+
        "shape. There are spiderwebs running between the balusters, "+
        "and a thick layer of dust cover the handrail. This part "+
        "of the corridor is barely lighted.\n");

    add_item("staircase",
        "The staircase is made with a dark wooden handrail that rise "+
        "to the third floor. These staircase seems that is not used a "+
        "lot. Dust and spiderwebs cover it, and the wood look without "+
        "shine or polish.\n");
                                                                         
    add_item("handrail",
        "A dark mate wood handrail rises to the third floor. "+
        "The handrail is covered up with a thick layer of dust.\n");
        
    add_item("balusters",
        "The slender poles, also known as balusters, are hard to "+
        "see because they are all covered with dust and spiderwebs.\n");
       
    add_item("walls",
        "The colors of the wallpaper that cover the walls of this "+
        "room are faded and muted, quite a contrast with the other "+
        "part of the corridor.\n");

    add_exit("castle2_04.c", "northwest");
    add_exit("castle3_01.c", "up");
    

    reset_room();

}                                           
