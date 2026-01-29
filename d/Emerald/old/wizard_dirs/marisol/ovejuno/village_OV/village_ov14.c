
/* Re Albi village. Village's path XIV.
 * Coded by Marisol (12/20/97)
 * Modified by Marisol (08/03/98) to be used in the village of
 * Ovejuno in Emerald.
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;

void
create_ov_room()
{

    set_long("A village path in Ovejuno. There is a small "+
        "cottage here. This is the house of Gorgi the clothier. "+
        "This cottage was made the same way like the clothier shop. "+
        "Wooden roof and white and red paint coat this cottage. "+
        "There is a small path to the north that goes back to the "+
        "main village path. The smokes of chimneys drift lazily in "+
        "the cool wind. High in the sky, puffy white clouds sail "+
        "with the mountain breeze.\n");

    add_item("clouds",
        "White puffy clouds like cotton candy sail softly "+
        "to the mountains. If you gaze closely to the clouds, "+
        "you will detect the outline of a majestic swan.\n");

    add_item(({"small cottage", "cottage"}),
        "This is a small cottage where the clothier lives. "+
        "Like the clothier's shop, it has a wooden roof, and is painted "+
        "white and red. There is some flower pots in the windowsills "+
        "that give to the cottage cheerful look.\n");              

    add_item(({"flower", "flowers", "pots", "windowsills"}),
        "The glass windows are framed with red paint like the "+
        "windowsills. Nice flowers pots with tulips and narcises "+
        "give a cheerful look to the cottage.\n");

    add_item(({"tulips", "narcises", "pots"}),
        "White snowish tulips and bright yellow narcises blossom "+
        "in the redish brown clay pots.\n");

    add_exit("village_ov13.c", "west");
    add_exit("village_ov04.c", "north");


}
