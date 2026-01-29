#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/icewall/local.h"
#include <macros.h>
inherit ICEOUTROOM;

void
create_icewall_room() 
{
   set_short("Up/Down Stairs");
   set_long("You are currently on a steep set of stairs carved into the face of "
	    + "the ice.  They go both up and down. "
	    + " \n");
   add_exit(ICE_OUT + "entrance","down");
   add_exit(ICE_OUT + "up_stairs2.c","up");
}
