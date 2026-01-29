/*
 *  /d/Sparkle/area/tutorial/town/street_3_ash.c
 *
 *  The destroyed version of this room.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit ASH_ROOM;

/* definitions */
// #define  TUTORIAL_CHAPTER    20  /* the chapter for the sign */

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

    add_exit("street_4_ash", "northeast");
    add_exit("general_store_ash", "southeast");
    add_exit("street_1_ash", "west");

    init_ash_room("outdoor");
} /* create_ash_room */


/*
 * Function name:       reset_room
 * Description  :       restore npc as needed
 */
public void
reset_room()
{
/*
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }
*/
} /* reset_room */



