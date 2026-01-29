#include "defs.h"

CONSTRUCT_ROOM {
    set_short("You are in the eastern part of a long room.");
    set_long("You are in the eastern part of a long room. A rudely cut "+
	     "passage continues east here. It looks like this passage is "+
	     "a fairly new one. (Everything is relative, perhaps it is only "+
	     "3-4 decades old, while the rest of the mines are several "+
	     "centuries old.)\n");
    add_item(({"opening","openings","exits"}),
	     "They lead to other other passages in the mines.");
    EXIT("longr1","west");
    EXIT("corridor","east");
}

		  
		    
