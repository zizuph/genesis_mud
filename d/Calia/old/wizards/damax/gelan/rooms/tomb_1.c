
/* 	this is a room of the town Gelan
 
    coder(s):   Damax  
 
    history:    11.02.93    Created                     Damax 
 
    purpose:    This is a room in the tomb. 
    exits:      South & north.  
 
    objects:    none
    npcs:       none
 
    quests:     none
    special:    none
 
    to do:      none
    bug:        none known
*/
 
 
inherit "/std/room";
#include "room.h"
#include <stdproperties.h>
#include <macros.h>
 
reset_room()
{
 
 
 
} /* reset_room */
 
create_room()
{
    /* descriptions */
 
    set_short("Tomb foyer");
    set_long(BS("You are in a smallish room north of the huge entrance.  You "+
                "notice that there are less cobwebs here, and that the dust "+
                "on the floor has been recently disturbed.  Perhaps you are "+
                "not the only living being down here..."+ 
 		"\n"));  
 
    /* properties */
 
    add_prop(ROOM_I_INSIDE, 1);		/* this room is inside */
 
    /* exits */
    
    add_exit(ROOM("tomb_2"), "north", 0);
    add_exit(ROOM("tomb_entrance"), "south", 0);
 

    /* items in the room */
 
    add_item(({"web","webs","spiderweb"}),
    BS("The spiderwebs are gray and dusty.  You wonder what made them.\n "));
    
    add_item(("dust"),
    BS("The dust here has been recently disturbed by something humanoid.\n"));

    call_out("reset_room", 1);
 
} /* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
