#include "defs.h"

CONSTRUCT_ROOM {
    set_short("You have entered a big hall");
    set_long(
	"You have entered a big hall. On the walls hang some faded "+
	"flannel carpets, and there is a huge wall-to-wall carpet on "+
	"the floor. The air is filled with a stinching smell of "+
	"sulfur, and thick smoke streams out of an opening in the "+
	"northern wall. There are two additional openings in the "+
	"western and eastern walls, though not as frightening as the "+
	"one in the north.\n");
    add_item(({"smell","sulfid","smoke","opening"}),
	"It really smells like some kind of awful dragon in there!");
    add_item(({"carpet","carpets"}),
	"They all seem to be faded and worn out, and in any case far " +
        "too heavy to carry.");
    EXIT("ovalroom","east");
    EXIT("draglair","north");
    EXIT("dopening","west");
}

		  
		    
