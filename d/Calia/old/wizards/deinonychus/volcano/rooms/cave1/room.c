/* File: sq.c */
/* Description: Part of the cave of Indy */

inherit "/std/room";

#include "cave1_room.h"

/*
 * Function name: create_room()
 * Description  : Create the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
create_room()
{
    set_short("");
    set_long(BS("\n"));
    add_exit(CAVE1DIR + "sq", "north", 0);
    add_exit(CAVE1DIR + "sq", "northeast", 0);
    add_exit(CAVE1DIR + "sq", "east", 0);
    add_exit(CAVE1DIR + "sq", "southeast", 0);
    add_exit(CAVE1DIR + "sq", "south", 0);
    add_exit(CAVE1DIR + "sq", "southwest", 0);
    add_exit(CAVE1DIR + "sq", "west", 0);
    add_exit(CAVE1DIR + "sq", "northwest", 0);
    call_out("reset_room", 1);
    add_prop(ROOM_I_LIGHT, 0);
}

/*****************************************************************************/

/*
 * Function name: reset_room()
 * Description:   Resets the room.
 * Arguments:     none
 * Returns:       nothing
 */

void
reset_room()
{
}

