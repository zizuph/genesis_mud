#include "defs.h"

CONSTRUCT_ROOM {

    set_short("The corridor straightens out here");
    set_long("The corridor straightens out here. The sloping gets abrupted "+
	     "by a level floor. This means, hopefully, that you are at the "+
	     "deepest level of the corridor now. It still stretches far out "+
	     "of sight to the east, but perhaps you are starting to reach "+
	     "the eastern part of Moria! Well, you'll have to continue to "+
	     "find out.\n");
    add_item(({"corridor","walls"}), 
	     "It is a vast corridor, having damp moisture clinging to the "+
	     "walls.");
    add_item(({"heat","moisture"}), 
	     "It is moisture of the water that trickles down from the walls "+
	     "and the ceiling.");
    add_item(({"floor","slope"}), 
	     "An amazingly sharp cut in the floor shows where the sloping "+
	     "begins.");
    EXIT("corr4", "west");
    EXIT("corr6", "east");
}
