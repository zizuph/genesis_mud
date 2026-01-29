#include "defs.h"

CONSTRUCT_ROOM 
{
    set_short("Dark tunnel");
    set_long("You are standing in a dark tunnel under what must be " +
	     "a north going tunnel. It is *very* narrow, so being " +
	     "claustrophobic here is probably not a good idea.\n");
    NORTH("exit3");
    SOUTH("exit1");
}
