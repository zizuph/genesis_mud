/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                31/5/96     call_outs taken out             Maniac
    		16.12.93    items changed		    Deinonychus
    		20. 2.93    path system                     Merlin
                10.01.93    descriptions                    Deinonychus
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    square
    exits:      nw-w-sw-s-se to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

#include "defs.h"
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
#include GUARD_INCLUDE

inherit GELAN_BASE_ROOM;

void
create_gelan_room()
{
    /* descriptions */
    set_short("Square corner north east");
    set_long(
      "You're in the northeast corner of the town square. To the north " +
      "you see the jail, hope you'll never end there. Looking east you see " +
      "a house of a citizen. You wish you would have a home like this one, " +
      "too. There are other interesting buildings all around the square.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);  	/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_en","south",0);
    add_exit(GELAN_ROOMS + "square_ne","west",0);
    add_exit(GELAN_ROOMS + "square_northend_e","northwest",0);
    add_exit(GELAN_ROOMS + "square_mide","southwest",0);
    add_exit(GELAN_ROOMS + "square_eastend_n","southeast",0);

    /* items in the room */

    add_item(({"jail", "prison"}), DESC("jail_house"));
    add_item(({"gate"}), DESC("jail_gate"));
    add_cmd_item(({"inscription"}), "read", DESC("jail_inscription"));
    add_item(({"house","citizen's house","citizen house"}),
        DESC("citizen_house"));
    add_item(({"buildings", "building"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}), DESC("floor"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
