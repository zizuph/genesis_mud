/* Corridor-second floor (1)
 * Coded by Marisol (09/25/98)
 * Marisol Ramos (c) 1998
 */


#pragma strict_types
#include "defs.h"
inherit CASTLE_OV2;


void
create_castle_room()
{    

    set_long("This corridor goes straight through the residence. "+
        "Two guards are posted in front of an impossing door. "+
        "More rooms are spread along the corridor.\n");

    add_item("guards",
        "These guards look alert to their environment. They look "+
        "quite strong too.\n");

    add_item("floor",
        "Beautiful porcelain tiles cover the floor of the corridor.\n");

    add_item(({"impossing door", "door"}),
        "An oak door with intricate carving is guarded by two guards. "+
        "Someone important seems to sleep there.\n");

    add_exit("castle2_01.c", "east");
    add_exit("castle2_03.c", "south");
    add_exit("castle2_06.c", "west");


    reset_room();
}
