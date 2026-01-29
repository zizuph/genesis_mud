#include "defs.h"

CONSTRUCT_ROOM 
{
    set_short("Dark tunnel");
    set_long("You are standing in a dark tunnel under what must be " +
	     "a north going tunnel. It is extremely narrow. It looks " +
	     "like you can crawl northward, though you should consider " +
	     "climbing up instead.\n");
    NORTH("exit2");
    UP("gate_room");
}
