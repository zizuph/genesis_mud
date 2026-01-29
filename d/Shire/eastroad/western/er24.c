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
 
   extraline = "The road runs east and west. "+
     "To the southeast you see some mounds and get a "+
       "feeling of dread. To the north are hills. The Great "+
	 "East Road continues east towards Bree. West of here "+
	   "you can see the Brandywine river.";
   
   add_item(({"mounds","mound"}),"The mounds you see  "+
	    "must be the Barrows.\n");
   add_item(({"hedge","bushes"}),"The bushes on the south "+
	    "side of the road comes from the east and heads along "+
	    "to road to Buckland.\n");
   add_item(({"hill","hills"}),"The hills are non-ending. "+
	    "They go on and on as far as you can see. and probalby "+
        "farther than that still.\n");
   add_item(({"river","brandywine","brandywine river"}),
	    "You can see the Brandywine river from here. You "+
	    "are glad that there is a bridge there. You would "+
	    "hate to have to swim a cross it.\n");
   
   add_exit(EAST_R_DIR + "er23","west",0,2);   
   add_exit(EAST_R_DIR + "er25","east",0,2);
   
   add_exit(EAST_R_DIR + "er24n","north","@@north_msg@@",2,1);
   add_exit(EAST_R_DIR + "er24s","south","@@south_msg@@",2,1);

}
