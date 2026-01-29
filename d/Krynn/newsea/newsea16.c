inherit "/std/room";

#include "local.h"

create_room()
{
   set_short("Road through the plains");
   set_long("You are walking along a well travelled road which leads " +
	    "through the mountains and to northern Solamnia. You notice " +
	    "that the plains south of you are full grown and healthy. To " +
	    "your east, the Vingaard River is undauntedly making his way " +
	    "north towards the sea.\n");
   
   add_exit(SOLAMN_PLAINS, "north");
/*add_exit(PARENT + "newsea15.c", "south", "@@construction");
*/
}


construction()
{
   write("The dwarves have closed the road in fear of an invasion, until " +
	 "the delegation of knights has successfully negotiated the " +
	 "reopening, no one is allowed to pass.\n");
   return 1;
}
