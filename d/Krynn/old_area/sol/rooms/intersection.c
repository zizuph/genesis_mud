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
   set_place(INTERSECTION);
   
   set_long_desc("Here the East road and the West road meets, intersecting " +
      "the Solace Main road. The Main road leads north and " +
      "south. The East road extends to the east, while the " +
      "West road extends to the west. A very large " +
      "vallenwood stands at the edge of the road here. A " +
      "rather large building is built in among the limbs, " +
      "and there is a wooden bridge-walk above your head " +
      "leading to the building.");
   
   add_exit(TDIR + "main_road5", "north");
   add_exit(TDIR + "east_road1", "east");
   add_exit(TDIR + "main_road6", "south");
   add_exit(TDIR + "west_road1", "west");
}


