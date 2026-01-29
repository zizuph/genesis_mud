#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Queen's platform");
    set_long("You are standing on the Queen's platform. The slightly raised "+
	     "platform is covered with a green velvet, and you notice the "+
	     "marks upon which a throne has once been placed. On the western "+
	     "wall there are heavy draperies, and the ballroom stretches "+
	     "east.\n");
    add_item(({"platform","velvet","marks","throne","ballroom"}),
	     "You see nothing special.");
    add_item(({"draperies","wall"}),
	     "The wall is covered with these silk-blue velvet draperies. "+
	     "However, they hide nothing apart from the dull western wall.");
    EAST("ballr");
}

		  
		    
