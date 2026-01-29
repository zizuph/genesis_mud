/*   Modification log:
 *
 *   -- Toby, 01-Oct-2007: Fixed typo.
 * 
 */

#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;

void
create_er_room()
{
  
   area = "close to";
   areaname = "the Great East Road";
   land = "Eriador";
   areatype = 1;
   areadesc = "field";
   grass = "green";
   
   extraline = "You are standing south of the Great East Road. "+
     "A thick hedge grows alongside the road. It runs north and south " +
     "and prevents you from going any further. A forest grows thick here.";
//   "to the Great East Road, and continues south to Buckland.";
   
   add_item(({"hedge","bushes"}),"The hedge on the east side of "+
	    "the road is quite thick. You don't think that you could "+
	    "get through to the other side of it.\n");
   add_item("forest","The forest on the west side of the road is "+
	    "not that thick. You hear the sounds of a river past the "+
	    "forest. Probably the Brandywine river.\n");
   add_item(({"road","dirt road"}),"The dirt road is pretty "+
	    "barren. It goes north to the Great East Road, and south "+
	    "to Buckland.\n");
   
   add_exit(EAST_R_DIR + "er24","north",0,2);
   add_exit(EAST_R_DIR + "er23s","west",0,2,1);   
//   add_exit(BUCK_L_DIR + "broad1","south","@@block_south@@",2);  
}

int
block_south()
{
   write("You are unable to make your way in that direction.\n");
   return 1;
}
