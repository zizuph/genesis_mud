/* Corridor-second floor (1)
 * Coded by Marisol (09/25/98)
 * Marisol Ramos (c) 1998
 */


#pragma strict_types

#include "../defs.h"

inherit CASTLE_OV2;

void
create_castle_room()
{    
    set_em_long("This corridor goes straight through the residence. "+
        "Two guards are posted in front of an impossing door. "+
        "More rooms are spread along the corridor.\n");

    add_item("guards",
        "These guards look alert to their environment. They look "+
        "quite strong too.\n");

    add_item("floor",
        "Beautiful porcelain tiles cover the floor of the corridor.\n");

    add_item(({"intrincate carvings", "carvings"}),
        "The door borders are carved with intrincate geometrical "+
        "figures, circles, ovals, squares and triangles of "+
        "incredible beauty and complexity.\n");

    add_exit("castle2_01", "east");
    add_exit("castle2_03", "south");
    add_door_exit(CASTLE_OBJ_DIR + "cdoor2_01", "castle2_06", "west");

}
