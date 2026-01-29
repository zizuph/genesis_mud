/*
 * AV4.c
 * - Alaron FEB 2000
 */

#include "defs.h"
#include <stdproperties.h>

inherit AVULAR_ROOM;


void
create_avular_room()
{
    set_short("A city street");
    set_em_long("The street rounds a sharp, narrow corner. The dark cobblestones of "+
        "the road form perfect, straight paths leading east and south. To the east, "+
        "a large, dome-shaped building is just barely visible beyond the edge of "+
        "the engulfing darkness. The southern path is completely obscured behind a "+
        "wall of absolute darkness.\n");

    add_item( ({"road", "cobblestone road", "dark road", "dark cobblestone road",
                "stones", "cobblestones", "dark stone", "dark stones"}),
             "The road is formed of thousands of small, dark stones. Each stone "+
             "is individually carved and uniquely shaped, yet the collection of "+
             "all of the stones somehow meshes together to form a narrow road.\n");

    add_item( ({"building", "buildings"}),
        "Several buildings peek out from behind the veil of suffocating blackness surrounding "+
        "this entire area. Each building is completely unique, some of them shaped like domes, "+
        "others traditionally shaped like rectangles or squares. In the distance, barely "+
        "visible on the edge of the darkness, a larger, dome-shaped building stands out "+
        "to the east.\n");

    add_item( ({"bush", "bushes"}),
        long("grass"));


    add_exit(AVMAIN+"av5", "east");
    add_exit(AVMAIN+"av3", "south");
}


