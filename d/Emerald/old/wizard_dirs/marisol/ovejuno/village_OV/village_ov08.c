
/* Re Albi village. Village's path VIII.
 * Coded by Marisol (12/12/97)
 * Modified by Marisol (07/29/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. At a distance you can see, "+
        "a lonely hut that lies at the end of the "+
        "path. There are no more houses in this part of the village. "+
        "Here and there you can see frolicking lambs in the high "+
        "pastures. The smokes of chimneys drift lazily in the cool "+
        "wind, and high in the sky, a hawk flies proudly with the "+
        "mountain breeze.\n");

    add_item("sheep",
        "High in the meadows, sheep are grazing the luscious "+
        "green grass. Lambs jump and frolick under the watching "+
        "eyes of the older sheep.\n");

    add_item("hawk",
        "A young hawk is flying in circles in the azure sky.\n");

    add_item("pastures",
       "The green pastures rise to the hill that hovers over the "+
       "village. Sheep and lambs roam in these communal lands "+
       "without any concerns.\n");

    add_exit("village_ov09.c", "northeast");
    add_exit("village_ov07.c", "southwest");

}                                                                    
