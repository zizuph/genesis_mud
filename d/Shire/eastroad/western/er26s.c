#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD;
 
void
create_er_room()
{
    area = "not far from";
    areaname = "the Great East Road";
    land = "Eriador";
    areatype = 7;
    areadesc = "small clearing";
    treetype = "willow";
 
    extraline = "The forest is very dense and very hard to "+
      "find your way in. South of here is too thick for you to "+
	"penetrate. West of here the forest ends. To the north "+
	  "you see a bush that makes way to the west.";
    
    add_item(({"surroundings","forest"}),
	     "Trees and bushes are all over the place. They make it "+
	     "hard to navigate through the forest. Most of the trees "+
	     "are willows.\n");
    
    add_item(({"bushes","bush"}),
	"It looks like it turns into a hedge in the east. Probably "+
	     "a very thick hedge.\n");
    
   set_noshow_obvious(1);
   add_exit(EAST_R_DIR + "er26","north",0,2);
   add_exit(EAST_R_DIR + "er25s","west",0,2);   
   add_exit(EAST_R_DIR + "er27s","east",0,2);
}
