
/* Re Albi village. Village's path XII.
 * Coded by Marisol (12/18/97)
 * Modified by Marisol (08/03/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. The path forks here to a small "+
        "trail to the southeast. The blacksmith's shop stands here, a "+
        "black and sturdy structure. You hear the strong and rhythmical "+
        "beating of a hammer over an anvil. In the distance you can "+
        "hear sheep bleating in the high pastures. Smokes rise from the "+
        "the smith's chimney, drifting lazily in the cool wind. "+
        "High in the sky, puffy white clouds sail with the "+
        "mountain breeze.\n");

    add_item("clouds",
        "White puffy clouds like cotton candy sail softly "+
        "to the mountains. If you gaze closely to the clouds, "+
        "you will detect the outline of a giant tree.\n");

    add_item(({"blacksmith's shop", "shop"}),
        "The blacksmith's shop is one of the strongest building "+
        "in the village. Ironfist, the blacksmith, is proud of his "+
        "handywork. He mends weapons and tools for the farmers and "+
        "guards from the elven lord's castle outside the village "+
        "of Ovejuno. He is also good making metal gates and fences "+
        "as his house's fence shows. It is said by the villagers that "+
        "the back of the shop has the best view to the far sea and "+
        "mountains. Usually some of the men of the village will go "+
        "during the afternoon to watch the view and talk about "+
        "the weather and other things that men are very "+
        "fond to chat.\n");

    add_exit("village_ov11.c", "northwest");
    add_exit("smith_shop_ov.c", "south");
    add_exit("village_ov16.c", "southeast");


}                                                                              
