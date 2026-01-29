/*
 * CASTLE_ROOM.c
 * Base inheritable file for all of the rooms in Castle Telberin
 *  - Revision September 11, 1996 by Alaron
 */

#include <stdproperties.h>

inherit "/std/room";

#pragma strict_types
#pragma save_binary

public void
create_room()
{
    set_short("Castle of Telberin");
    set_long("An unmodified castle room.\n");

    add_item(({"floor", "ground"}),
	     "The floor is made of smooth, polished marble. It must have "+
	     "taken centuries for all of this marble to have been "+
	     "located, cut, shaved, smoothed and placed in neat tiles "+
	     "throughout the entire castle. You wonder just how many "+
	     "hours of work hundreds of elves put into constructing "+
	     "this wonder.\n");
    
    add_item(({"ceiling", "up"}),
	     "Thick, dark oak boards support the white chalked ceiling. "+
	     "Underneath tbe boards, intricate patterns in deep green "+
	     "leaves cover the stone.\n");

    add_item(({"walls", "emerald stone", "green stone walls", 
	       "stone walls", "lines", "stones"}),
	     "The walls are made of an intriguing emerald green stone "+
	     "which seems to radiate and glow. The stones were so "+
	     "expertly carved and shaped that you have to squint and "+
	     "struggle to see the lines where the stones were joined. The "+
	     "walls are decorated with thin borders of leaves.\n");
    
    add_item(({"border", "borders", "thin borders", "leaves"}),
	     "There is a thin border of leaves painted in a deep "+
	     "green color near the ceiling and near the floor. In addition "+
	     "you notice several long, living vines winding through "+
	     "the dark oak boards near the ceiling.\n");

    add_item(({"vines", "long vines", "living vines"}),
	     "You are amazed that vines such as those winding through "+
	     "the oak boards in the ceiling are still alive within the "+
	     "confines of the castle. In fact, they seem to be thriving "+
	     "in here, almost as if they were feeding off of the strange, "+
	     "green glow eminating from the walls.\n");

    add_item("light","The light is an enchanting mystical green light. "+
	     "It seems to emanate from everywhere.\n");

    add_prop(ROOM_I_INSIDE, 1);
}

    
