/*
 * AV$2.c
 * Fork in the road in Avular
 * - Alaron JAN 2000
 */

#include "defs.h"
#include <stdproperties.h>

inherit AVULAR_ROOM;


void
create_avular_room()
{
    set_short("A city intersection");
    set_em_long("The dark cobblestone road forms a crossroads here. Three "+
        "sections of road come together to form a small, stone circle. One branch "+
        "of the road heads east toward a massive, twisting bridge. The other "+
        "branches of the road continue to the northwest and southwest, disappearing "+
        "into the darkness amidst dozens of buildings of varied shapes, sizes and "+
        "styles.\n");

    add_item( ({"road", "cobblestone road", "dark road", "dark cobblestone road",
                "stones", "cobblestones", "dark stone", "dark stones"}),
             "The road is formed of thousands of small, dark stones. Each stone "+
             "is individually carved and uniquely shaped, yet the collection of "+
             "all of the stones somehow meshes together to form a narrow road.\n");

    add_item( ({"east", "bridge", "massive bridge", "serpent", "snake",
                "snake bridge", "serpentine bridge", "stone bridge"}),
             "To the east, almost completely hidden within the darkness lies a "+
             "massive stone bridge. It winds to the right, then left, then back "+
             "again as it arches up and over a street passing beneath. The bridge "+
             "appears to be carved in the shape of a massive snake.\n");

    add_item( ({"circle", "stone circle", "small circle", "small stone circle",
                "crossroads"}),
             "The circle in the center of this area is the meeting point of three "+
             "branches of the dark cobblestone road. It is made up of the same "+
             "intricately carved stones that comprise the rest of the road.\n");

    add_item( ({"building", "buildings"}),
             "The buildings are barely visible through the darkness. Some are short "+
             "and round, while others vary in height, their rooves made of jagged, "+
             "inconsistent beams of stone and wood. You can't see much more than that "+
             "through the eerie darkness from here.\n");

    add_exit(AVMAIN+"av3", "northwest");
    add_exit(AVMAIN+"av2", "east");
    add_exit(AVMAIN+"av9", "southwest");
}


