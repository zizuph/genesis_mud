
/* Re Albi village. Village's path XIII.
 * Coded by Marisol (12/19/97)
 * Copyright (c) Marisol Ramos 1997 */

#pragma strict_types
#pragma no_clone
#include "/sys/stdproperties.h"
#include "/d/Emerald/sys/macros.h"
#define WDOOR DOORS+"weaver_out.c"
#include "defs.h"
inherit OV_VILLAGE;

object door;
void reset_room()
{
}

void
create_ov_room()
{

    set_long("A village path in Ovejuno. Clothier Gorgi's shop "+
        "is at the end of this path. A wooden sign hangs "+
        "from a wooden pole. There is another path to the east. "+
        "In the distance you can hear sheep bleating in the high "+
        "pastures. The smokes of chimneys drift lazily in the cool "+
        "wind. High in the sky, puffy white clouds sail with the "+
        "mountain breeze.\n");

    add_item("clouds",
        "White puffy clouds like cotton candy sail softly "+
        "to the mountains. If you gaze closely to the clouds, "+
        "you will detect the outline of a dancing bear.\n"); 

    add_item(({"clothier gorgi's shop", "shop", "gorgi's shop"}),
        "This is a large, one story house that lodge Gorgi the "+
        "Clothier. He sales different apparel of dress "+
        "like tunics, blouses, skirts and breeches for both the "+
        "village and the castle. In contrast to other houses in "+
        "village, Gorgi place has a sturdy wooden roof and white "+
        "and yellow paint coat the wooden boards. Gorgi is known as "+
        "a good trader. He doesn't weave or sew clothes but he has "+
        "connections that let him bring any kind of clothes "+
        "to his store.\n");

    add_item(({"sign", "wooden sign"}),
        "It is a wooden sign that reads: Clothier Gorgi Shop.\n");

    add_cmd_item(({"sign", "wooden sign"}), ({"read", "exa", "examine"}),
        "It is a wooden sign that reads: Clothier Gorgi Shop.\n");

reset_room();

setuid();
seteuid(getuid());
door= clone_object(WDOOR);
door->move(TO);

    add_exit("village_ov03.c", "north");
    add_exit("village_ov14.c", "east");


}                                                               
