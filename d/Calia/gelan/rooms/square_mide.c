/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    31/5/96     call_outs taken out             Maniac
                20. 2.93    path system                     Merlin
                2.02.93    descriptions		            Deinonychus
	         3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      all except sw to square

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
    /* descriptions */

    set_short("Square mid east");
    set_long("You're in the mideast of the townsquare. To your " +
	"northwest you see the famous pillory of Gelan. Southwestwards is " +
	"the beautiful fountain. Around the whole square you see other " +
	"interesting buildings.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);			/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_ne","north",0);
    add_exit(GELAN_ROOMS + "square_fountain_ne","south",0);
    add_exit(GELAN_ROOMS + "square_central_e","west",0);
    add_exit(GELAN_ROOMS + "square_en","east",0);
    add_exit(GELAN_ROOMS + "pillory_e","northwest",0);
    add_exit(GELAN_ROOMS + "square_corner_ne","northeast",0);
    add_exit(GELAN_ROOMS + "square_e","southeast",0);

    /* items in the room */

    add_item("pillory", DESC("pillory"));
    add_cmd_item("sign", "read", DESC("pillory_sign"));
    add_item("fountain", DESC("fountain"));
    add_item(({"floor", "ground", "bottom", "square"}), DESC("floor"));
    add_item(({"building", "buildings"}), DESC("buildings"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
