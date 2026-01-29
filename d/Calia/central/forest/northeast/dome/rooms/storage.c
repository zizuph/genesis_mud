// ROOM:  Dome - kitchen storage
//        DOME_ROOMS + room08

    /*  Calia Domain

        HISTORY
        1998-09-06 Created by Khon.
        1999-July-19 Seriously revamped by Khon.

        PURPOSE
        Here food is stored and preserved, awaiting its time
        to be transformed into delectible delights.
        Unicorn quest might require components from this room,
        food items the players must collect and prepare
        properly.
        Also the entrance to Benobodrome's secret hideout.

        AREA HISTORY
        Benobodrome was often struck by a desire for a strange
        delicacy at the oddest hours, and so had a secret
        passage built to this room from his private retreat.

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

    set_short("Pleasure Dome kitchen storage");

    set_long("To be determined.\n");

    /* ITEMS */

    add_item(({"shelves"}),
        "This is a faint trail running east-west through the " +
        "to travel anywhere off the trail.\n");

    add_item(({"shelf"}),
        "Which shelf? There are eight different shelves.\n");

    /* EXITS */

    add_exit("entrance", "north", 0, 05);
    add_exit("kitchen", "east", 0, 05);

    /* PROPERTIES */

    add_prop(ROOM_I_LIGHT, 1);
    add_prop(ROOM_I_HIDE, 50);

    }
