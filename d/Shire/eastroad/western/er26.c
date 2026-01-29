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
 
   extraline = "North of here you see hills. South there "+
     "is a hedge in front of a thinning forest. East the "+
       "road continues to the city of Bree. West of here is "+
	 "the Brandywine river past the road to Buckland.";
   
   add_item("forest","The forest is not as thick as it "+
	    "looks to be in the east. You see the forest ending "+
	    "to the west of here. You notice a thin fog southwest "+
	    "of here. You have a feeling of dread when you look in "+
	    "that direction.\n");
   add_item(({"hedge","bushes"}),"The bushes line the south "+
	    "side of the road here. They seem a bit thin. In the "+
	    "west they look thicker. The hedge ends in the east.\n");
   add_item(({"hill","hills"}),"The hills are north of here. "+
	    "They look empty and barron. You wonder if anything "+
	    "is out by the plain rocky hills.\n\nProbably nothing.\n");
   add_item(({"river","brandywine","brandywine river"}),
	    "The river is still a bit away, and hard to see. But you "+
	    "know like almost everybody else that it is there. It is "+
	    "probably close to the road to Buckland.\n");
   
   add_exit(EAST_R_DIR + "er25","west",0,2);   
   add_exit(EAST_R_DIR + "er27","east",0,2);
   
   add_exit(EAST_R_DIR + "er26n","north","@@north_msg@@",2,1);
   add_exit(EAST_R_DIR + "er26s","south","@@south_msg@@",2,1);

} 
