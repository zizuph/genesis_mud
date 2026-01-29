/*
 *  /d/Sparkle/area/tutorial/town/road_1_ash.cc
 *
 *  The destroyed version of this room.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit ASH_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    10  /* the chapter for the sign */


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

    add_exit("road_0_ash", "south");
    add_exit("street_1_ash", "north");

    init_ash_room("outdoor", 1);
} /* create_ash_room */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    object   npc;

    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */


