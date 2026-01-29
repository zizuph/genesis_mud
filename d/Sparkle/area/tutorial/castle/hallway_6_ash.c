/*
 *  /d/Sparkle/area/tutorial/castle/hallway_5_ash.c
 *
 *  The destroyed version of this room.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit ASH_ROOM;

/* Definitions */
#define  TUTORIAL_CHAPTER    39  /* the chapter for the sign */

/* prototypes */
public void        create_ash_room();
public void        reset_room();


/*
 * Function name:        create_ash_room
 * Description  :        set up the room
 */
public void
create_ash_room()
{
    reset_room();

    add_exit("hallway_6n_ash", "north");
    add_exit("hallway_5_ash", "east");
    add_exit("hallway_6s_ash", "south");
    add_exit("dungeon_ash", "down");

    init_ash_room("castle");

    reset_room();
} /* create_ash_room */


/*
 * Function name:       reset_room
 * Description  :       restore signs and npcs as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */