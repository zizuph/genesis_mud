
/* Re Albi village. Village's path XV.
 * Coded by Marisol (12/22/97)
 * Modified by Marisol (08/03/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#include "/d/Emerald/sys/macros.h";
#pragma strict_types
#include "defs.h"
#define GHDOOR DOORS + "sh_in"
inherit OV_VILLAGE;


object ghdoor;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. A shepherd's house "+
        "is at the middle of the curve. The path continue to the "+
        "nortwest to the communal pastures. In the distance, "+
        "you see a shepherd watching the flock. Lambs "+
        "are frolicking in the high pastures. The smokes of "+
        "chimneys drift lazily in the cool wind. A soft breeze "+
        "entices your sense with a very faint salty tang mingles with "+
        "woodland.\n");


    add_item("sheep",
        "Sheep are the main industry of the village of Ovejuno. "+
        "They provide meat and wool to be consume in the village "+
        "and some is traded with the roving gypsies and other "+
        "traders that come through the mountain caravan.\n");

    add_item("pastures",
        "The green pastures rise to the hill that hovers over the "+
        "village. Sheep and lambs roam in these communal lands "+
        "without any concerns.\n");

    add_item("house",
        "A shepherd's house. It is like the rest of the houses in "+
        "the village, wood and thatch roof with two small windows. "+
        "There is a hole in the roof where smoke drifts out with the "+
        "wind. A wooden door opens to the outside.\n");

    add_item("shepherd",
        "The shepherd is too far away to see his features. "+
        "From this distance you can see that he is standing in "+
        "the pasture, holding his staff, watching the playful "+
        "lambs.\n");

    add_exit("village_ov04.c", "south");
    add_exit("pastures/pastures01", "northwest");

    ghdoor= clone_object(GHDOOR);
    ghdoor->move(TO);

}
                                                                  
