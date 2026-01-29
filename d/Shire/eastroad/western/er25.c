#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
 
void 
create_er_room()
{
   area = "on";
   areaname = "the Great East Road";
   land = "Eriador";
   areatype = 8;
   areadesc = "the land";
 
	extraline = "There is a hedge here on the south side of the " +
        "road. Hills cover most of what you see to the north. " +
        "The road continues east to the city of Bree. West of here " +
        "is the road to Buckland and the Brandywine river.";
   
   add_item("forest","The forest has ended and the signs "+
	    "of a forest is to the east.\n");
   add_item(({"hedge","bushes"}),
       "The hedge is on the south side of the road and is thick " +
       "here, preventing travellers from going that way. However, "+
       "there is a a part of the hedge that is thin enough for " +
       "travellers to pass through.\n");
   add_item(({"hill","hills"}),"Hills and more hills are north "+
		"of here.\n");
   add_item(({"river","brandywine","brandywine river"}),
	    "You can barley see the Brandywine river. It is "+
	    "in the west past a road that is angling  south "+
	    "from the Great Eastroad.\n");
 
   add_exit(EAST_R_DIR + "er24","west",0,2);   
   add_exit(EAST_R_DIR + "er26","east",0,2);
   
   add_exit(EAST_R_DIR + "er25n","north","@@north_msg@@",2,1);
   add_exit(EAST_R_DIR + "er25s","south",0,2);

} 
