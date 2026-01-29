/*
 *  /d/Sparkle/area/tutorial/castle/library.c
 *
 *  Within the castle of Baron von Krolock.
 *
 *  Created August 2019, by Arman
 */
#pragma strict_types
#include "/d/Sparkle/area/tutorial/defs.h"

inherit ASH_ROOM;

/* Prototypes */
public void        create_ash_room();

/* definitions */
#define  TUTORIAL_CHAPTER    20  /* the chapter for the sign */

/*
 * Function name:        create_ash_room
 * Description  :        set up the room
 */
public void
create_ash_room()
{
    reset_room();

    add_exit("hallway_4_ash", "west");

    init_ash_room("castle");
} /* create_ash_room */

/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void 
reset_room()
{
    if (!present("_tutorial_sign"))
    {
        add_sign(TUTORIAL_CHAPTER);
    }

} /* reset_room */