/*
 * Expanded section of the Great East Road
 * Finwe, March 2005
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
   
   area = "not far"; /* Distance from areaname */
   areaname = "Westmarch";
   land = "Eriador";
   areatype = 10;
   areadesc = "rolling plain";
   grass = "green";
   
   extraline = "The road is straight, and runs east and west. It passes " +
   "through rich meadows and past hills. The road is packed hard from " +
   "countless travellers that have used it. It is wide and bare of any " +
   "vegetation.";

   add_item(({"meadow","meadows"}),"The meadows to the north and south "+
   "look wholesome and refreshing.\n");

   add_item(({"hills","hill","rolling hills","tower hills","far downs"}),
   "This area is made of hills, hills and more hills. The Far Downs "+
   "wrinkle the surface of the earth to the east, as the Tower Hills "+
   "do so in the west. In between are these hills, which make "+
   "up a great deal of Westmarch.\n");

   add_item(({"hobbit holes","hobbit-holes","holes"}),
   "The hobbit holes around here are dug right into the "+
   "sides of the hills, a convenient arrangement to be sure. "+
   "They look reasonably big and not too crowded, though "+
   "it seems impossible to enter them.\n");

   add_exit(EAST_R_DIR + "er3","west");
   add_exit(EAST_R_DIR + "er3b","east");
   add_exit(EAST_R_DIR + "er3nb","north",0,2,1);
   add_exit(EAST_R_DIR + "er3sb","south",0,2,1);
}

void leave_shire()
{
}