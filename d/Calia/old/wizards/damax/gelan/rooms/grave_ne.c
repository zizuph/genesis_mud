
/* 	this is a room of the town Gelan
 
    coder(s):   Damax  
 
    history:    08.02.93    Comma spacing changed 
		05.02.93    Created                      Damax
 
    purpose:    The NE corner of the graveyard in Gelan
    exits:      south, west and southwest
 
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
 
    set_short("The northeast corner of the graveyard");
    set_long(BS("This is the northeastern corner of the graveyard.  The "+
                "path turns south here and also goes west.  You see a "+
                "huge willow to the southwest.  There are few "+
                "tombstones here, as if room is being made for more. "+
                "\n"));  
 
    /* properties */
 
    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
 
    /* exits */
 
    add_exit(ROOM("grave_n"), "west", 0);
    add_exit(ROOM("grave_e"), "south", 0);
    add_exit(ROOM("grave_tree"), "southwest", 0);

    /* items in the room */
 
    add_item(({"grave", "tombstone", "graves", "tombstones"}), 
    BS("The tombstones here are pure white marble, and a small wreath "+
       "decorates each grave.  The epitaph on one stone catches your eye.  "+
       "It reads: IRONUS BARISORIL - GIANT SLAYER, FATHER, FRIEND\n"));

    add_item(({"tree", "willow", "willow tree", "knoll", "small knoll"}),
    BS("On top of the small grassy knoll to the southwest stands a huge "+
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
