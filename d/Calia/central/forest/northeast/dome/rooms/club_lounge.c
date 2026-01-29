// ROOM:  Dome - Club VIP lounge
//        DOME_ROOMS + club_lounge

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        Here the hedonists enjoy the best of everything.
 
        AREA HISTORY
        The barracks and mess hall are unrecognisable from
        thier origional state, being totally rebuilt into
        luxerious quarters rivalling Benobodromes private
        quarters.

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

    set_short("Pleasure Dome VIP lounge");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"forest", "tree", "trees"}),
        ".\n");

    /* EXITS */

    add_exit("club_library", "east", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
