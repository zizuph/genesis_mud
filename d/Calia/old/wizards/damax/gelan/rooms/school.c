/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    20. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    learn general skills here
    exits:      west to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

create_room()
{
    /* descriptions */

    set_short("School");
    set_long(BS("School\n"));

	/* properties */

    add_prop(ROOM_I_INSIDE, 1);					/* this room is inside */

    /* exits */

    add_exit(ROOM("square_eastend_n"),"west",0);

    /* items in the room */

    add_item(({"%", "%"}), BS("%\n"));

    call_out("reset_room", 1);

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
