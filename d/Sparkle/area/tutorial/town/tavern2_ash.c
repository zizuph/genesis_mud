/*
 *  /d/Sparkle/area/tutorial/town/tavern2_ash.cc
 *
 *  The destroyed version of this room.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit ASH_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    18  /* the chapter for the sign */

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

    add_exit("tavern_ash", "east");

    init_ash_room("indoor", 2);
} /* create_ash_room */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
} /* reset_room */



