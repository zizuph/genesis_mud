#include "defs.h"

CONSTRUCT_ROOM {
    set_short("The northern passage");
    set_long("You are in the northern passage. The passage is blocked to "+
	     "the north due to a rockslide, but it continues to the south. "+
	     "It is possible to climb one of the blocks, or you can go east "+
	     "into an opening.\n");
    add_item(({"rockslide","rock","passage","blocks","opening"}),
	     "You see nothing special.");
    EXIT("onblock","up");
    EXIT("npass1","south");
    EXIT("throne","east");
}

		  
		    
