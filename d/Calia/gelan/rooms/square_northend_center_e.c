/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                31/5/96     call_outs taken out             Maniac
    		02.02.95    typo removed 		    Deinonychus
    		16.12.93    items changed		    Deinonychus
    		21. 2.93    path system                     Merlin
	        21.12.92    descriptions		    Deinonychus
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      all except ne to square

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
    set_short("Square northend center east");
    set_long(
      "You're in the north of the town square. To the north-east you see " +
      "the guards quarter where you can get useful information. Looking " +
      "southwards you see the pillory where you can perhaps throw " +
      "tomatoes at some poor fellows. All around the place you see " +
      "other interesting buildings.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "castle_road_e1","north",0);
    add_exit(GELAN_ROOMS + "pillory_e","south",0);
    add_exit(GELAN_ROOMS + "square_northend_center_w","west",0);
    add_exit(GELAN_ROOMS + "square_northend_e","east",0);
    add_exit(GELAN_ROOMS + "castle_road_w1","northwest",0);
    add_exit(GELAN_ROOMS + "pillory_w","southwest",0);
    add_exit(GELAN_ROOMS + "square_ne","southeast",0);

    /* items in the room */

    add_item("quarter", DESC("police_house"));
    add_item("pillory", DESC("pillory"));
    add_item(({"buildings", "building","jail"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}), DESC("floor"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
