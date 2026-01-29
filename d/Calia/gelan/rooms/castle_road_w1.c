/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                31/5/96    call_outs taken out              Maniac
    		15.12.93    items changed		    Deinonychus
    		15. 2.93    path/guard system installed     Merlin
	        14.12.92    improvement of descriptions     Deinonychus
	        12.12.92    descriptions and items	    Deinonychus
                 6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    road to castle
    exits:      n-ne-e to road, sw-s-se to square

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      nothing at the moment
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
    set_short("castle road west");
    set_long("You're in the castle road. To the northwest you see the " +
      "guards armoury. Westwards is the famous Calia Inn, a really funny " +
      "looking building. You see " +
      "some more interesting looking buildings east, southeast and " +
      "southwest of here.\n");
      
	/* properties */

    add_prop(ROOM_I_INSIDE, 0);	  /* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "castle_road_w2","north",0);
    add_exit(GELAN_ROOMS + "square_northend_center_w","south",0);
    add_exit(GELAN_ROOMS + "castle_road_e1","east",0);
    add_exit(GELAN_ROOMS + "castle_road_e2","northeast",0);
    add_exit(GELAN_ROOMS + "square_northend_w","southwest",0);
    add_exit(GELAN_ROOMS + "square_northend_center_e","southeast",0);

    /* items in the room */

    add_item("armoury", DESC("armoury_house"));
    add_item("inn", DESC("inn_house"));
    add_item("sign", DESC("inn_sign"));
    add_item(({"road","floor","ground","bottom"}), DESC("floor"));
    add_item(({"building", "buildings"}), DESC("buildings"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
