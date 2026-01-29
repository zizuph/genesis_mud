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
 
   extraline = "South of here is a forest. North you see "+
   "hills and more hills. The road continues east to the "+
   "city of Bree. West of here is the Brandywine river "+
   "and the Barrow Downs.";
 
   add_item("forest","The forest does not see that hard to "+
      "move through as it does to the east. You see the "+
      "forest thinning out to the west. You notice that "+
      "where the forest thins out a hedge marks the south "+
      "side of the road.\n");
   add_item(({"hedge","bushes"}),"You can't tell much about "+
      "the hedge. Perhaps if you go west you can see it "+
      "better.\n");
   add_item(({"hill","hills"}),"The hills are non-ending. "+
      "You wonder if anything is out by the plain rocky "+
      "hills.\n\nProbably nothing.\n");
	add_item(({"river","brandywine","brandywine river"}),
      "The river is still to far away to see. But you know "+
      "like almost everybody else that it is there. It is "+
      "probably close to the road to Buckland.\n");
 
   add_exit(EAST_R_DIR + "er26","west",0,2);   
   add_exit(EAST_R_DIR + "er28","east",0,2);
   
   add_exit(EAST_R_DIR + "er27n","north","@@north_msg@@",2,1);
   add_exit(EAST_R_DIR + "er27s","south","@@south_msg@@",2,1);
} 






