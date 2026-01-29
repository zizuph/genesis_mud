/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:    
        31/5/96     call_outs taken out             Maniac
        21. 2.93    path system                     Merlin
        2.02.93    descriptions		            Deinonychus
        3.11.92    created                         Merlin
        6.11.92    installed help system           Merlin

    purpose:    square
    exits:      all to square

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

    set_short("Square west north");
    set_long("You're in the northern west of the townsquare. To your " +
        "northwest you see the alchemist's house. Around the whole square " +
        "you see other interesting buildings.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "square_corner_nw","north",0);
    add_exit(GELAN_ROOMS + "square_w","south",0);
    add_exit(GELAN_ROOMS + "square_westend_n","west",0);
    add_exit(GELAN_ROOMS + "square_midw","east",0);
    add_exit(GELAN_ROOMS + "square_nw","northeast",0);
    add_exit(GELAN_ROOMS + "square_westend","southwest",0);
    add_exit(GELAN_ROOMS + "square_fountain_nw","southeast",0);

    /* items in the room */

    add_item(({"alchemist's house", "house"}), DESC("alchemist_house"));
    add_item(({"floor", "ground", "bottom", "square"}), DESC("floor"));
    add_item(({"building", "buildings"}), DESC("buildings"));
    add_item(({"%", "%"}), BS("%\n"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
