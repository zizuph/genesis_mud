/*
 *  /d/Sparkle/area/tutorial/castle/hallway_5.c
 *
 *  Within the castle of Baron von Krolock.
 *
 *  Created September 2005, by Cooper Sherry (Gorboth)
 */
#pragma strict_types
#include "../defs.h"

inherit CASTLE_DIR + "castle_room";

/* Prototypes */
public void        create_castle_room();
public void        reset_room();


/*
 * Function name:    create_castle_room
 * Description  :    set up the room
 */
public void
create_castle_room()
{
    set_short("in a narrow hallway of the castle");
    set_long("The hallway narrows here, where an archway separates"
      + " the eastern from the western portion of the corridor. A feeling"
      + " of uneasiness strikes you about travelling west. To the east,"
      + " you feel as if you have a better chance of getting out of this"
      + " fearful place.\n\n");

    add_item( ({ "arch", "archway" }),
        "An archway provides a point at which this hallway can be"
      + " controlled by guards, if there are any present.\n");
    add_item( ({ "hall", "hallway", "corridor", "west", "east" }),
        "The hallway travels both east and west.\n");

    add_castle_items();
    add_torch_items();

    add_exit("hallway_4", "east");
    add_exit("hallway_6", "west", check_exit, 1, 0);

    set_trigger_room("hallway");
    reset_room();
} /* create_castle_room */


/*
 * Function name:        reset_room
 * Description  :        clone npcs and tutorial signs as needed
 */
public void
reset_room()
{
    clone_guard(2);
} /* reset_room */

