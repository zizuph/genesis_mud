
/* 	this is a room of the town Gelan
 
    coder(s):   Damax  
 
    history:    08.02.93    Total rehaul                 Damax 
		07.02.93    Created                      Damax
 
    purpose:    The tree in the center of the graveyard in Gelan
    exits:      All directions except up.  
 
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
 
    set_short("The tree in the centre of the graveyard");
    set_long(BS("You are standing before a huge willow at the centre of the "+
                "graveyard.  There are no graves here on the grassy knoll, "+
                "but you sense some presence within the tree.  You feel safe "+
                "here, but you also sense that anything not welcome in this "+
                "graveyard might not feel as confident in its safety.  "+
                "The graveyard lies in all directions.  "+ 
                "\n"));  
 
    /* properties */
 
    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
 
    /* exits */
    
    set_noshow_obvious(1);
    add_exit(ROOM("grave_n"), "north", 0);
    add_exit(ROOM("grave_nw"), "northwest", 0);
    add_exit(ROOM("grave_w"), "west", 0);
    add_exit(ROOM("grave_sw"), "southwest", 0);
    add_exit(ROOM("grave_s"), "south", 0);
    add_exit(ROOM("grave_se"), "southeast", 0);
    add_exit(ROOM("tomb_entrance"), "down", 0);
    add_exit(ROOM("grave_e"), "east", 0);
    add_exit(ROOM("grave_ne"), "northeast", 0);
 

    /* items in the room */
 
    add_item(({"grave","tombstone","graves","tombstones"}), 
    BS(GO_CLOSER)); 

    add_item(({"tree","willow","willow tree","knoll","small knoll"}),
    BS("The huge willow looks ancient, its dry, yellow bark akin to the "+
       "wrinkles in an aged human's face.  The branches brush the ground, "+
       "and you notice that the ground at the base of the tree is very "+
       "fertile.  You wonder what could be fertilizing this tree...\n"));

    add_item(({"path","cobbled path"}),
    BS(GO_CLOSER)); 
 
    add_item(({"flower","flower bed","floweers","flower beds"}),
    BS(GO_CLOSER));

    call_out("reset_room", 1);
 
} /* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
