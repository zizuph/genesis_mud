#include "defs.h"

CONSTRUCT_ROOM {
    set_short("Entrance of a vast corridor");
    set_long("Entrance of a vast corridor. You are standing at the "+
	     "entrance of a vast corridor, stretching as far as you can "+
	     "see to the east. The walls are smooth and it is obvious that "+
	     "this was the main road in the Mines, long time ago.\n");
    EXIT("corr1", "east");
    EXIT("longr2", "west");
}
