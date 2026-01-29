// ROOM:  Dome - Art Museum
//        DOME_ROOMS + museum

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        Dedicated to momentous moments in the domes history
        of artistic achievement, these exhibits are less
        magnificent than the entry hall exhibits, but more
        meaningfull and educational.
 
        AREA HISTORY
        Once Benobodromes harem room, after the Shrews walked
        out it was somewhat neclected and eventually used to
        store artworks in progress and unsatisfactory 
        projects. It eventually evolved into an exhibit of
        art in the making.

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

    set_short("Pleasure Dome art museum");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"forest", "tree", "trees"}),
        ".\n");

    /* EXITS */

    add_exit("common", "south", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
