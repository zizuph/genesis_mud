/*
 *  /d/Sparkle/area/tutorial/cliffs/cliffroad_4.c
 *
 *  A road in the cliffs leading toward Krolock's castle.
 *
 *  Created November 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit SD_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    42  /* the chapter for the sign */

/* prototypes */
public void        create_silverdell();


/*
 * Function name:        create_silverdell
 * Description  :        set up the room
 */
public void
create_silverdell()
{
    set_short("on a narrow path leading up through the cliffs");
    set_long("The path leading up through the cliffs travels a"
      + " ways to the south here, winding its way past a number"
      + " of tall boulders.\n\n");

    add_outdoor_items();
    add_cliffs_items();

    add_item( ({ "here", "area" }), long);
    add_item( ({ "boulder", "boulders", "tall boulder",
                 "tall boulders" }),
        "Just west of the path, a number of tall boulders lean"
      + " down over you.\n");

    add_exit("cliffroad_3", "northeast");
    add_exit("cliffroad_5", "south");

    //This room is instanced.
    instance_entrance = 0;

    reset_room();
} /* create_silverdell */


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
