/* 	this is a room of the town Gelan

    coder(s):   Merlin

    history:     28/5/96    updated                          Maniac
                 20. 2.93    path system                     Merlin
                 2.02.93    descriptions		    Deinonychus
	         3.11.92    created                         Merlin
                 6.11.92    installed help system           Merlin

    purpose:    square
    exits:      n-ne to pillory, nw-w-sw-e to square, s to fountain

    objects:    none
    npcs:       none

    quests:     none
    special:    none

    to do:      none
    bug:        none known
*/


#pragma save_binary

#include "room.h"

inherit SQUARE_ROOM;
#include GUARD_INCLUDE
#include <stdproperties.h>
#include <macros.h>

void
create_room()
{
    create_square_room();
    
    /* descriptions */

    set_short("Square central west");
    set_long("You're at a central point in the town square. To your " +
        "north you see the famous pillory of Gelan, while southwards is " +
        "the beautiful fountain. All around the square you see " +
        "interesting buildings.\n");

	/* properties */

    add_prop(ROOM_I_INSIDE, 0);	/* this room is outside */

    /* exits */

    add_exit(GELAN_ROOMS + "pillory_w","north",0);
    add_exit(GELAN_ROOMS + "fountain_northend_w","south",0);
    add_exit(GELAN_ROOMS + "square_midw","west",0);
    add_exit(GELAN_ROOMS + "square_central_e","east",0);
    add_exit(GELAN_ROOMS + "square_nw","northwest",0);
    add_exit(GELAN_ROOMS + "pillory_e","northeast",0);
    add_exit(GELAN_ROOMS + "square_fountain_nw","southwest",0);

    /* items in the room */

    add_item("pillory", DESC("pillory"));

} /* create_room */

/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
