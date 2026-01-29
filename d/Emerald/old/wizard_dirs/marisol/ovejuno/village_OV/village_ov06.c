

/* Re Albi village. Village's path VI.
 * Coded by Marisol (12/6/97)
 * Modified by Marisol (07/28/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. Humble houses are "+
        "scattered in the village. To the west, two big wooden "+
        "building loom over the path. To the east, the path continue "+
        "forging ahead inside the village. To the north, a small trail "+
        "goes to a stone fountain. In the distance you can hear "+
        "sheep bleating in the high pastures. The smokes of chimneys "+
        "drift lazily in the cool wind, and high in the sky, a "+
        "golden eagle flies gracefully with the sea breeze.\n");

    add_item(({"golden eagle", "eagle"}),
        "A graceful golden eagle sails the sky. Golden eagles are "+
        "majestic bird of prey that fly long distance over "+
        "mountains and forests. The one in the sky "+
        "is a nice specimen of its kind. Its yellow feathers shine "+
        "brightly with the sunlight.\n");

    add_exit("village_ov07", "east");
    add_exit("village_ov05", "west");
    add_exit("ov_fountain.c", "north");

}                                                              
