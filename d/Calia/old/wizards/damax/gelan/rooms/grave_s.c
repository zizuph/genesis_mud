
/* 	this is a room of the town Gelan
 
    coder(s):   Damax  
 
    history:    08.02.93    Comma spacing fixed          Damax  
		07.02.93    Created                      Damax
 
    purpose:    The S end of the graveyard in Gelan
    exits:      west, north and east  
 
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
 
    set_short("The south end of the graveyard");
    set_long(BS("This is the southern end of the graveyard.  The "+
                "path heads west and east from here.  You see a "+
                "huge willow to the north.  There are many gray "+
                "tombstones here. "+
                "\n"));  
 
    /* properties */
 
    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
 
    /* exits */
 
    add_exit(ROOM("grave_se"), "east", 0);
    add_exit(ROOM("grave_tree"), "north", 0);
    add_exit(ROOM("grave_sw"), "west", 0);

    /* items in the room */
 
    add_item(({"grave", "tombstone", "graves", "tombstones"}), 
    BS("The tombstones here are dark granite, and a small wreath "+
       "decorates each grave.  The epitaph on one stone catches your eye.  "+
       "It reads: LLIRANDELL - FALLEN BUT NOT FORGOTTEN\n"));

    add_item(({"tree", "willow", "willow tree", "knoll", "small knoll"}),
    BS("On top of the small grassy knoll to the north stands a huge "+
       "weeping willow.  It looks ancient, and appears to be standing watch "+
       "over the entire graveyard.\n"));  

    add_item(({"path", "cobbled path"}),
    BS("The path is cobbled with many smooth, colourful stones.  You "+
       "wouldn't be surprised if the craftsmanship were Hobbit.\n"));
 
    add_item(({"flower", "flower bed", "floweers", "flower beds"}),
    BS("The flower beds are beautiful and in full bloom.  What colours!\n"));

    add_item(({"wreath", "wreaths", "wreathes"}),
    BS("The wreath on each grave is woven from violets and a single white "+
       "rose.\n"));
 
    call_out("reset_room", 1);
 
} /* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
