/*
 *  /d/Sparkle/area/tutorial/castle/hallway_4_ash.c
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

    add_exit("hallway_3n_ash", "north");
    add_exit("hallway_5_ash", "west");
    add_exit("castle_library_ash", "east");
    add_exit("hallway_3s_ash", "south");

    init_ash_room("castle");
} /* create_ash_room */




