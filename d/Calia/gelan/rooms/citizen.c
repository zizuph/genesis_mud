/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    15. 2.93    path system installed           Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    house of a citizen
    exits:      south to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

create_room()
{
    /* descriptions */

    set_short("Citizen");
    set_long(BS("Citizen\n"));

	/* properties */

    add_prop(ROOM_I_INSIDE, 1);					/* this room is inside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_eastend_n", "south", 0);

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
