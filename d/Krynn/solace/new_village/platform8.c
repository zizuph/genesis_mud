/*
* The village Solace
*
* By Rastlin
*/
#include "local.h"
#include "/d/Krynn/common/defs.h"

inherit SOLOUTROOM;

create_solace_room()
{
   set_place(PLATFORM);
   
   set_long_desc("This is a rather large platform. Here is a stairway " +
      "winding its way around the trunk to the West road of " +
      "Solace. The bridgewalk extends to the northeast and " +
      "south. There is a building opened to the northwest. ");
   
   add_exit(TDIR + "bank", "northwest");
   add_exit(TDIR + "bridge_walk25", "northeast");
   add_exit(TDIR + "bridge_walk24", "south");
   add_exit(TDIR + "west_road6", "down");
}


