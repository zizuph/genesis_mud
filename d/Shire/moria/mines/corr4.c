#include "defs.h"

CONSTRUCT_ROOM {

    set_short("You're walking a vast, gently sloping corridor");
    set_long("You're walking a vast, gently sloping corridor. There seems "+
	     "to be no end in either direction. You can feel the heat down "+
	     "here, deep under the mountain. You probably have mountain "+
	     "several thousands of feet above you, and the warm fire of the "+
	     "earth, can not be far below you. There also is an exit in the "+
	     "southern wall here.\n");
    add_item(({"corridor","walls"}), 
	     "It is a vast corridor, having damp moisture clinging to the "+
	     "walls.");
    add_item(({"heat","moisture"}), 
	     "It is moisture of the water that trickles down from the walls "+
	     "and the ceiling.");
    EXIT("corr3", "west");
    EXIT("corr5", "east");
    SOUTH("gallhall");
}
