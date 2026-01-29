/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    24. 2.93    removed error                   Merlin
                16. 2.93    path system                     Merlin
                17. 1.93    new guard system                Merlin
                14. 1.93    path server                     Merlin
                 9. 1.93    townrooms.h -> room.h           Merlin
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    room for guards to stay
    exits:      east to palace road, up to restroom, down to powdery

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

    set_short("Guards armoury south west");
    set_long(BS("Guards armoury south west\n"));

	/* properties */

    add_prop(ROOM_I_INSIDE, 1);					/* this room is inside */

    /* exits */

    add_exit(GELAN_ROOMS + "palace_road_sw","east",0);
    add_exit(GELAN_ROOMS + "gate","southeast",0);
    add_exit(GELAN_ROOMS + "guards_restroom_sw","up",0);
    add_exit(GELAN_ROOMS + "guards_powdery_sw","down",0);

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