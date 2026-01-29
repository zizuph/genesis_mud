/*      this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                31/5/96     call_outs taken out             Maniac
    		15.12.93    items changed		    Deinonychus
    		12. 2.93    path/guard system installed     Merlin
	        14.12.92    descriptions                    Deinonychus
	         6.11.92    installed help system           Merlin
                 3.11.92    created                         Merlin

    purpose:    road to castle
    exits:      east to guards, n-nw-w to castle road, s-sw-se to square

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
    set_short("castle road east");
    set_long("You're in the castle road. To your east there's the " +
        "guards quarters where you can find help and information. " +
        "There are more interesting buildings south and west of here.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);   /* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "castle_road_e2","north",0);
    add_exit(GELAN_ROOMS + "square_northend_center_e","south",0);
    add_exit(GELAN_ROOMS + "castle_road_w1","west",0);
    add_exit(GELAN_ROOMS + "guards_info","east",0);
    add_exit(GELAN_ROOMS + "castle_road_w2","northwest",0);
    add_exit(GELAN_ROOMS + "square_northend_center_w","southwest",0);
    add_exit(GELAN_ROOMS + "square_northend_e","southeast",0);

    /* items in the room */

    add_item(({"quarter", "quarters"}), DESC("police_building"));
    add_item(({"road","floor","ground","bottom"}), DESC("floor"));
    add_item(({"building", "buildings"}), DESC("buildings"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
