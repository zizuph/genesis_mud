/*
 *  /d/Sparkle/area/tutorial/castle/portcullis_ash.c
 *
 *  The destroyed version of this room.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit ASH_ROOM;

/* prototypes */
public void        create_ash_room();


/*
 * Function name:        create_ash_room
 * Description  :        set up the room
 */
public void
create_ash_room()
{
    reset_room();

    add_exit("entrance_ash", "west");
    add_exit("outside_castle", "east");

    init_ash_room("castle", 1);
} /* create_ash_room */




