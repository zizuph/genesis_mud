// ROOM:  Dome - Wardrobe
//        DOME_ROOMS + wardrobe
    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        Here dedicated tailors, weavers, dyers and armourers
        diligently work at their trade, improving thier
        skills and also selling clothing and armour to 
        visitors and members.
 
        AREA HISTORY
        Origionally a smithy, the hedonists soon did away
        with unpleasant, heavy and cumbersome metal armours.
        Looking for stylish and enjoyable alternatives, they
        came up with padded, leather and silk armours.

    */

// INCLUSIONS AND DEFINITIONS

inherit "/std/room.c";

#include "defs.h"
#include <stdproperties.h>

// ROOM DEFINITION

void
create_room()
{

    /* DESCRIPTION */

    set_short("Pleasure Dome wardrobe");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"forest", "tree", "trees"}),
        ".\n");

    /* EXITS */

    add_exit("common", "west", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
