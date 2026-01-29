/*
 *  /d/Sparkle/area/tutorial/town/street_6_ash.c
 *
 *  The destroyed version of this room.
 *
 *  Created April 2017, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit ASH_ROOM;

/* definitions */
#define  TUTORIAL_CHAPTER    30  /* the chapter for the sign */

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

    add_exit("street_7_ash", "north");
    add_exit("human_start_ash", "northeast");
    add_exit("elf_start_ash", "east");
    add_exit("hobbit_start_ash", "southeast");
    add_exit("street_5_ash", "south");
    add_exit("goblin_start_ash", "southwest");
    add_exit("gnome_start_ash", "west");
    add_exit("dwarf_start_ash", "northwest");

    init_ash_room("outdoor");
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



