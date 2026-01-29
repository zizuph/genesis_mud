// ROOM:  Dome - Common Lounge
//        DOME_ROOMS + common

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        Here visitors can relax and enjoy the wonders of the
        pleasure dome. Drinks and snacks are available.

        AREA HISTORY
        Origionally Benobodrones throneroom, this area was
        converted by his less egotistical successors into
        a common area. It's the largest room in the dome.

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

    set_short("Pleasure Dome common lounge");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"forest", "tree", "trees"}),
        ".\n");

    /* EXITS */

    add_exit("museum", "north", 0, 05);
    add_exit("hall", "west", 0, 05);
    add_exit("club_entrance", "south", 0, 05);
    add_exit("arsenal", "southeast", 0, 05);
    add_exit("wardrobe", "east", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
