/* 	this is a room of the town Gelan
 
    coder(s):   Merlin
 
    history:     4.11.92    creation                        Merlin
 
    purpose:	home of the head guard
    exits:      none
 
    objects:    head guard
    npcs:       none
 
    quests:     none
    special:    none
 
    to do:      equip the head guard
                fix when several attacks arrive (divide up guards then)
                build room to other rooms
    bug:        none known
*/
 
 
#pragma save_binary

inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
 
reset_room()
{
 
    object guard;
 
    if(!present("galiburn"))
    {
 
        guard = clone_object(GELAN_MONSTERS + "head_guard");
        guard->move(this_object());
        tell_room(this_object(), QNAME(guard) + " arrives and starts to control "
                                 + "the guards.\n");
    }
 
} /* reset_room */
 
create_room()
{
    /* descriptions */
 
    set_short("Head guard office");
    set_long(BS("Description will follow later\n"));
 
	/* properties */
 
    add_prop(ROOM_I_INSIDE, 1);					/* this room is inside */
 
    /* exits */
 
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
