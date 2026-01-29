/*
 *  /d/Sparkle/area/tutorial/castle/hallway_1s_ash.c
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

    add_exit("hallway_2s_ash", "west");
    add_exit("entrance_ash", "north");

    init_ash_room("castle", 2);
} /* create_ash_room */
