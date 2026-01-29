
/* Re Albi village. Village's path IX.
 * Coded by Marisol (12/12/97)
 * Modified by Marisol(07/29/98) to be used in the village of
 * Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. The path continue to the "+
        "northeast where the sage femme's hut lies. "+
        "There are not more houses in this part of the village. High "+
        "in the rising meadows, lambs frolick happily. "+
        "The smokes of chimneys drift lazily in the cool wind, and "+
        "high in the sky, a hawk flies proudly with the mountain "+
        "breeze.\n");

    add_item("sheep",
        "Grazing sheep morosely eat grass and flowers in the "+
        "steep meadows of the communal pastures.\n");

    add_item("hawk",
        "A hawk flies in circles with the mountain breeze.\n");

    add_item(({"pastures", "meadows"}),
        "A green meadows with wildflowers rise to the hill "+
        "that hovers over the village. This is the communal pastures "+
        "where the village's sheep graze mindlessly.\n");

    add_exit("village_ov10.c", "northeast");
    add_exit("village_ov08.c", "southwest");

}                                                                    
