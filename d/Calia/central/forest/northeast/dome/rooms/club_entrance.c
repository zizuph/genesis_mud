// ROOM:  Dome - Club entrance
//        DOME_ROOMS + club_entrance

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        This is where the dedicated hedonists seperate
        themselves from the outside world. One cannot enjoy
        perfection amongst the ignorance of the
        unsophisticated.
 
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

    set_short("Pleasure Dome VIP entrance");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"forest", "tree", "trees"}),
        ".\n");

    /* EXITS */

    add_exit("common", "north", 0, 05);
    add_exit("kitchen", "west", 0, 05);
    add_exit("club_library", "south", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
