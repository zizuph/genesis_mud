
/* 	this is a room of the town Gelan
 
    coder(s):   Damax  
 
    history:    09.02.93    Created                     Damax 
 
    purpose:    This is a tomb entrance underneath the main graveyard. 
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
 
    set_short("Secret entrance to tomb");
    set_long(BS("You now stand in a rough hewn cavern deep underneath the "+
                "graveyard.  The walls and ceiling are "+ 
                "cut in the rough shape of a domed cathedral, and you can "+
                "see several etched carvings, much like those on the arch "+
		"at the graveyard entrance.  A hole in the south wall "+
                "leads to a dark, steep tunnel heading back to the surface, "+
                "and there is also an open passage cut into the north wall. "+
                "\n"));  
 
    /* properties */
 
    add_prop(ROOM_I_INSIDE, 1);		/* this room is inside */
 
    /* exits */
    
    add_exit(ROOM("grave_tree"), "south", 0);
    add_exit(ROOM("tomb_1"), "north", 0);
 

    /* items in the room */
 
    add_item(({"web","webs","spiderweb"}),
    BS("The spiderwebs are gray and dusty.  You wonder what made them.\n"));
    
    add_item(({"carvings","etchings"}),
    BS("The carvings are those of cherubs and the like...you think that "+ 
       "this place might have once been a tomb.\n")); 

    call_out("reset_room", 1);
 
} /* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
