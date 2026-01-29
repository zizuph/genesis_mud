/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                31/5/96     call_outs taken out             Maniac
    		16.12.93    items changed		    Deinonychus
    		21. 2.93    path system                     Merlin
                10.01.92    descriptions                    Deinonychus
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    square
    exits:      west to pillory, all except ne to square

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

public void
create_gelan_room()
{
    set_short("Square north east");
    set_long(
      "You're in the northeast of the town square. To the northeast " +
      "you see the jail, hope you'll never end there. Looking west you see " +
      "the pillory and be sure it is still in use. There are other " +
      "interesting buildings all around the square.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);					/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_northend_e","north",0);
    add_exit(GELAN_ROOMS + "square_mide","south",0);
    add_exit(GELAN_ROOMS + "pillory_e","west",0);
    add_exit(GELAN_ROOMS + "square_corner_ne","east",0);
    add_exit(GELAN_ROOMS + "square_northend_center_e","northwest",0);
    add_exit(GELAN_ROOMS + "square_central_e","southwest",0);
    add_exit(GELAN_ROOMS + "square_en","southeast",0);

    /* items in the room */

    add_item(({"jail", "prison"}), DESC("jail_house"));
    add_item(({"gate"}), DESC("jail_gate"));
    add_cmd_item(({"inscription"}), "read", DESC("jail_inscription"));
    add_item("pillory", DESC("pillory"));
    add_item(({"buildings", "building"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}), DESC("floor"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
