
/* Re Albi village. Village's path III.
 * Coded by Marisol (12/4/97)
 * Modified by Marisol (07/28/98) to be used in the village of Ovejuno
 * in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;
                                  
void
create_ov_room()
{

    set_long("A village path in Ovejuno. The path goes straight "+ 
        "to the village. To the south, there is another path that "+
        "goes to a clothes's shop. Houses are scattered on both side of "+
        "the path. Here and there you can see frolicking "+
        "lambs in the high pastures. The smokes of chimneys drift "+
        "lazily in the cool wind, and high in the sky, a falcon "+
        "flies proudly with the wind.\n");

    add_item("sheep",
        "Sheep are the main trade in Ovejuno. The wool is not of great  "+
        "quality but is good enough to weave a nice and durable textile "+
        "that is good for trade. In the pastures, playful "+
        "lambs are frolicking under the watchful eyes of the "+
        "older sheep.\n");

    add_item("falcon",
        "A white and brown barred fishing falcon. Maybe an "+
        "Peregrine-falcon. They love to fly inland to fish in the "+
        "rivers and creeks of the mountains.\n");   
 
    add_item("pastures",
        "The green pastures rise to the hill that hovers over the "+
        "village. Sheep and lambs roam in these communal lands "+
        "without any concerns.\n");       

    add_exit("village_ov04.c", "east");
    add_exit("village_ov02.c", "west");
    add_exit("village_ov13.c", "south");


}                  
