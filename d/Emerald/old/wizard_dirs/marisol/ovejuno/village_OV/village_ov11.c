
/* Re Albi village. Village's path XI.
 * Coded by Marisol (12/16/97)
 * Modified by Marisol (08/03/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#include "/d/Emerald/sys/macros.h";
#pragma strict_types
#include "defs.h"
#define SMDOOR DOORS + "sm_in"
inherit OV_VILLAGE;

object smdoor;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. The path turns north "+
        "to the blacksmith's shop. Faintly you hear the "+
        "rhythmical beating of a hammer over an anvil. A sturdy "+
        "house rises besides the path. In the distance you can hear "+
        "sheep bleating in the high pastures. The smokes of chimneys "+
        "drift lazily in the cool wind, and high in the sky, puffy "+
        "white clouds sail with the mountain breeze.\n");

    add_item("clouds",
        "White puffy clouds like cotton candy sail softly "+
        "to the mountains. If you gaze closely to the clouds, "+
        "you will detect the outline of a huge bear.\n");

    add_item(({"sturdy house", "house"}),
        "This sturdy house belongs to the blacksmith and his family. "+
        "It looks stronger than the rest of the houses in the "+
        "village. A metal fence with an intricate metalwork surrounds "+
        "the porch, giving the house an elegant outlook. An open "+
        "door leads to the house.\n");

    add_item(({"metal fence", "fence"}),
        "A beautiful piece of metalwork. Flowers, leaves and fruits "+
        "are intermingled to create a picture of metal beauty.\n");


    add_exit("village_ov12.c", "southeast");
    add_exit("village_ov07.c", "northwest");

    smdoor= clone_object(SMDOOR);
    smdoor->move(TO);


}                                        
