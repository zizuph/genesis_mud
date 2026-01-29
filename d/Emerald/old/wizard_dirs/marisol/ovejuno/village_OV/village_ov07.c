
/* Re Albi village. Village's path VII.
 * Coded by Marisol (12/11/97)
 * Modified by Marisol (07/28/98) to be used in the village of 
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#pragma no_clone
#include "/sys/stdproperties.h"
#include "/d/Emerald/sys/macros.h"
#define PDOOR DOORS+"duffer_out.c"
#include "defs.h"
inherit OV_VILLAGE;


object door;

void
reset_room()
{
}


void
create_ov_room()
{

    set_long("A village path in Ovejuno. There is an intersection "+
        "here. To the northeast, a path winds away from the village. "+
        "To the southeast, you hear the rhythmical beating of a hammer "+ 
        "over an anvil. On both sides of the paths, wood and straw "+
        "houses are scattered. There is also a small hut in the "+
        "north side of the path. In the distance, you can hear "+
        "sheep bleating in the high pastures. The smoke of chimneys "+
        "drift lazily in the cool wind, and high in the sky, puffy "+
        "white clouds sail with the sea breeze.\n");

    add_item("clouds",
        "White puffy clouds like cotton candy sails softly "+
        "to the mountains. If you gaze closely to the clouds, "+
        "you will detect the outline of a flying dragon.\n");

    add_item("hut",
        "A small hut made of discard wooden boards and a straw roof. "+
        "In the front walls of the hut, old pots and tools "+
        "and even an old javelin, hang from rusty nails.\n");

    add_item(({"boards", "wooden boards"}),
        "These boards look like something discarded from the general "+
        "store dry fish wooden boxes. You can even smell still the "+
        "stink.\n");

    add_item(({"roof", "straw roof"}),
        "The roof looks battered and old. The straw roof has holes in "+
        "it. You wonder if the roof leaks inside the hut.\n");

    add_item(({"pots", "tools", "javelin"}),
        "They are so old and worn-down that they are useless to "+
        "anyone. But maybe they are out here to show the trade of the "+
        "hut's owner.\n");

reset_room();

door = clone_object (PDOOR);
door->move(TO);

    add_exit("village_ov08.c", "northeast");
    add_exit("village_ov11.c", "southeast");
    add_exit("village_ov06.c", "west");


}                                                                       
