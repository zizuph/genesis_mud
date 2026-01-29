/* Re Albi village. Village's path II.
 * Coded by Marisol (12/2/97)
 * Copyright (c) Marisol Ramos 1997 */
/* Modified by Marisol (07/12/98) For the village of Ovejuno in Emerald
 *Copyright (c) Marisol Ramos 1998*/


#pragma strict_types
#include "defs.h"
inherit OV_VILLAGE;



void
create_ov_room()
{

    set_long("A village path in Ovejuno. The path goes to the "+
        "plateau where the village is settled. This plateau is known "+
        "as the Tabla Rasa, the Flat Table. This meseta is ideal to "+
        "the human settlement to build their houses and rise sheep "+
        "for local consumption and trade. The plateau is surround by "+
        "hills and at the end of the village a path goes down to the "+
        "inland valleys. On both sides of the path, houses are "+
        "scattered around. Here and there you can see frolicking "+
        "lambs in the high pastures. The smoke of chimneys drift "+
        "lazily in the cool wind, and high in the sky, a falcon "+
        "flies proudly with the wind.\n");

    add_item("sheep",
        "Sheep are the main trade in Ovejuno. The wool is not of "+
        "great quality but is good enough to weave nice and durable "+
        "textiles to be trade with the roaming caravan that visit "+
        "this village during most part of the year. Also some of the "+
        "sheep is used for local consumption as meat.\n");

    add_item("falcon",
      "A white and brown barred fishing falcon. Maybe an "+
      "Peregrine-falcon. They love to fly inland to fish in the "+
      "rivers and creeks of the mountains.\n");

    add_item("pastures",
      "The green pastures rise to the hill that hovers over the "+
      "village. Sheep and lambs roam in these communal lands "+
      "without any concerns.\n");

    add_exit("village_ov03.c", "east");
    add_exit("village_ov01.c", "west");


}
