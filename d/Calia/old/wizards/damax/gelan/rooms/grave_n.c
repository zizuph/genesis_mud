
/* 	this is a room of the town Gelan
 
    coder(s):   Damax  
 
    history:    08.02.93    Comma spacing fixed          Damax 
		05.02.93    Created                      Damax
 
    purpose:    The N end of the graveyard
    exits:      north, south, east and west
 
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
 
    set_short("The north end of the graveyard");
    set_long(BS("You are standing in the north end of the graveyard.  The "+
                "gate is directly north of you, and the huge willow is to "+
                "your south.  A cobbled path winds its way east and west "+
                "from here amongst the tombstones. "+
                "\n"));  
 
    /* properties */
 
    add_prop(ROOM_I_INSIDE, 0);		/* this room is outside */
 
    /* exits */
 
    add_exit(ROOM("grave_entrance"), "north", 0);
    add_exit(ROOM("grave_nw"), "west", 0);
    add_exit(ROOM("grave_ne"), "east", 0);
    add_exit(ROOM("grave_tree"), "south", 0);
    /* items in the room */
 
    add_item(({"grave", "tombstone", "graves", "tombstones"}), 
    BS("The tombstones here are pure white marble, and a small wreath "+
       "decorates each grave.  The epitaph on one stone catches your eye.  "+
       "It reads: PEREGRIN - FALLEN FALCON, KNIGHT OF CALIA\n"));

    add_item(({"tree", "willow", "willow tree", "knoll", "small knoll"}),
    BS("On the top of the small grassy knoll to the south stands a huge "+
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
 
    add_item(({"gate", "entrance", "arch", "archway"}),
    BS("The archway north of here, the exit to this graveyard, looks to "+
       "be an exquisite work of art.  Maybe you should take a closer "+
       "look.\n"));

    call_out("reset_room", 1);
 
} /* create_room */
 
/*
 * Function name: none
 * Description:   none
 * Arguments:     none
 * Returns:       none
 */
