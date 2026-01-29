#include "defs.h"

CONSTRUCT_ROOM {
    set_short("On huge rock in the north passage.");
    set_long("You stand on top of a huge rock in the north passage. There "+
	     "is a small hole in the wall to a shaft leading up.\n");
    add_item(({"block","hole","shaft"}),"You see nothing special");
    EXIT("npass2","down");
    EXIT("window","up");
}

		  
		    
