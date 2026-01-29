/*
 * AV3.c
 * - Alaron JAN 2000
 */

#include "defs.h"
#include <stdproperties.h>

inherit AVULAR_ROOM;


void
create_avular_room()
{
    set_short("A city street");
    set_em_long("The narrow, dark cobblestone road slopes down and back up again in "+
        "a random wave. On either side of the dark road, appearing just out of the "+
        "oppressive darkness, are the dim forms of various buildings. Between the road "+
        "and the dim forms of the building lie rows of the strange, white-bladed grass and "+
        "colorless bushes. The street continues to the north and southwest.\n");

    add_item( ({"road", "cobblestone road", "dark road", "dark cobblestone road",
                "stones", "cobblestones", "dark stone", "dark stones"}),
             "The road is formed of thousands of small, dark stones. Each stone "+
             "is individually carved and uniquely shaped, yet the collection of "+
             "all of the stones somehow meshes together to form a narrow road. It "+
             "slopes down, then up, and down again in a random wave shape. The undulating "+
             "path is so smooth, you actually notice that some of the cobblestones have "+
             "been shaped with a curve to enhance the effect.\n");

    add_item( ({"building", "buildings"}),
        "Several buildings peek out from behind the veil of suffocating blackness surrounding "+
        "this entire area. Each building is completely unique, some of them shaped like domes, "+
        "others traditionally shaped like rectangles or squares.\n");

    add_item( ({"bush", "bushes"}),
        long("grass"));


    add_exit(AVMAIN+"av4", "north");
    add_exit(AVMAIN+"av42", "southwest");
}


