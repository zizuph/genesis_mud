// ROOM:  Dome - Club library
//        DOME_ROOMS + club_library

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.

        PURPOSE
        Here the hedonists have gathered all of their
        written works, countless scrolls and texts of art,
        poetry, novels, manuals on technique and philosophy.
        The club bullatin board as well.
 
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

    set_short("Pleasure Dome library");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"forest", "tree", "trees"}),
        ".\n");

    /* EXITS */

    add_exit("club_entrance", "north", 0, 05);
    add_exit("club_lounge", "west", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
