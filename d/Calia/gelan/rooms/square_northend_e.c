/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    
                31/5/96     call_outs taken out             Maniac
    		03.02.95    typos removed		    Deinonychus
    		16.12.93    items changed		    Deinonychus
    		21. 2.93    path system                     Merlin
                21.12.92    descriptions		    Deinonychus
                 3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      sw to pillory, east to jail, north to info office,
                se-s-w to square, nw to castle road

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
    set_short("Square northend east");
    set_long(
      "You're in the north of the town square. To the north you see " +
      "the guards quarter where you can get useful information. Looking " +
      "southwestwards you see the pillory where you can throw tomatoes at " +
      "some poor fellows in the pillory.  East of here is the jail and it's " +
      "said that no prisoner escaped so far.  All around the place you see " +
      "other interesting buildings.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "guards_info","north",0);
    add_exit(GELAN_ROOMS + "square_ne","south",0);
    add_exit(GELAN_ROOMS + "square_northend_center_e","west",0);
    add_exit(GELAN_ROOMS + "guards_jail_nice","east","@@block");
    add_exit(GELAN_ROOMS + "castle_road_e1","northwest",0);
    add_exit(GELAN_ROOMS + "pillory_e","southwest",0);
    add_exit(GELAN_ROOMS + "square_corner_ne","southeast",0);

    /* items in the room */

    add_item("quarter", DESC("police_house"));
    add_item(({"jail","prison"}), DESC("jail_house"));
    add_item(({"gate"}), DESC("jail_gate"));
    add_cmd_item(({"inscription"}), "read", DESC("jail_inscription"));
    add_item("pillory", DESC("pillory"));
    add_item(({"buildings", "building"}), DESC("buildings"));
    add_item(({"square", "floor","ground","bottom","road"}), DESC("floor"));

} /* create_room */

/*
 * Function name: block
 * Description:   blocks a player
 * Arguments:     none
 * Returns:       1
 */
int block()
{
  write("You don't want to go into the jail, do you?\n");
  return 1;
}

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
