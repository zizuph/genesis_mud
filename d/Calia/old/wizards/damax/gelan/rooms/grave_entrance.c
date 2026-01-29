

/* 	this is a room of the town Gelan
 
    coder(s):   Damax  
 
    history:    08.02.93    Comma spacing fixed            Damax 
		07.02.93    Typo fixed *blush*             Damax 
                03.02.93    Created                        Damax  
 
    purpose:    The entrance to the graveyard in Gelan	
    exits:      south 
 
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
 
    set_short("Graveyard entrance");
    set_long(BS("You are standing at the entrance to a beautiflu "+
                "graveyard. A huge marble archway spans the entrance, its "+
                "surface etched with flowing chancery and lifelike cherubs.  "+
                "A low granite wall surrounds the entire graveyard, "+
                "protecting the lush lawns and blooming flowers from stray "+
                "animals and careless passersby.  "+  
                "\n"));  
 
    /* properties */
 
    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
 
    /* exits */
 
    add_exit(ROOM("grave_n"), "south", 0);
    
    /* items in the room */
 
    add_item(({"grave", "tombstone", "graves", "tombstones"}), 
    BS(GO_CLOSER));

    add_item(({"wall", "granite", "granite wall"}),
    BS("The wall is low, smooth and finely crafted by Gelan stonemasons.\n"));

    add_item(({"arch", "archway", "entrance", "marble", "marble arch"}),
    BS("The archway is exquisitely crafted, and perhaps the finest artistic "+
      "creation you've seen that has been made by human hands.\n"));

    add_item(({"flower", "flower bed", "floweers", "flower beds"}),
    BS(GO_CLOSER));

    add_item(({"lawn", "lawns", "grass", "lush lawn", "lush lawns"}),
    BS(GO_CLOSER));

    call_out("reset_room", 1);
 
} /* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
