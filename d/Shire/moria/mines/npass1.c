#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Beginning of northern passage");
    set_long("This is the beginning of the northern passage. It is a wide "+
	     "passage which seems to have been regularly used. The floor "+
	     "has been made with lots of effort, but is now criss-crossed "+
	     "with cracks and grooves. The passage lies north and south, "+
             "and there is an opening to the east.\n");
    add_item(({"passage","floor","opening"}),"You see nothing special.");
    add_item(({"cracks","crack","groove","grooves"}),
	     "They seem safe to cross though.");
    EXIT("npass2","north");
    EXIT("mjunc","south");
    EXIT("sqchambe","east");
}

		  
		    
