#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Magnificient knights' hall!");
    set_long("You're in the magnificient knights' hall! The walls are "+
	     "covered with shields and armours, relics from the past, when "+
	     "the King under the Mountain still reigned and his kingdom "+
	     "reached far outside the Mountains. There are two exits, west "+
	     "through a door-way and east towards an armoury.\n");
    add_item(({"shields","armours","relics"}),
	     "They are so securely fastened, that you cannot possibly pry "+
	     "them off.");
    add_item(({"exit","exits"}),"East or west?");
    add_item(({"door-way","west"}),
	     "It looks like it leads towards a slippery shimmering room.");
    add_item(({"east","armoury"}),
	     "Rather go east and have a better look, eh?");
    EAST("armoury");
    WEST("losttrck");
}

		  
		    
