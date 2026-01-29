/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    16. 2.93    path system installed           Merlin
                17. 1.93    new guard system                Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    room for guards to stay
    exits:      eats to castle road, up to restroom, down to powdery

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

    set_short("Guards armoury north");
    set_long(BS("Guards armoury north\n"));

	/* properties */

    add_prop(ROOM_I_INSIDE, 1);					/* this room is inside */

    /* exits */

    add_exit(GELAN_ROOMS + "castle_road_w2","east",0);
    add_exit(GELAN_ROOMS + "guards_restroom_n","up",0);
    add_exit(GELAN_ROOMS + "guards_powdery_n","down",0);

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
