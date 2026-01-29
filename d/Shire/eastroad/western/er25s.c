#pragma save_binary
#pragma strict_types

#include "local.h"
inherit EAST_ROAD;

#define BDOWNS_DIR   "/d/Shire/downs/road/"

void
create_er_room()
{
 
  area = "close to";
  areaname = "the Great East Road";
  land = "Eriador";
  areatype = 9;
  areadesc = "path";
  
    extraline = "A thick hedge lines the Great East Road in the " +
        "north. The path you are on heads south. You get a feeling " +
        "of dread when you look south. East of here is a forest. " +
        "A tall hedge is west of here and a path leads north or south.";
  
    add_item(({"hedge","bushes"}),"The hedge to the north is " +
        "thick, lining the path. The rest of the hedge continues " +
        "to the west and does not seem passable in any manner.\n");
  add_item("forest","The forest on the east side of the path is "+
	   "not that thick. You could probably make your way into the "+
	   "forest if you are careful.\n");
  add_item("path","The path is pretty barren. It goes south "+
	   "into the fog and north towards a road.\n");
  
  add_exit(EAST_R_DIR + "er25","north",0,2);
  add_exit(EAST_R_DIR + "er26s","east",0,2,1);
  add_exit(BDOWNS_DIR + "road01","south",0,2);     
//  add_exit(B_DOWNS_DIR + "slope3","south",0,2);     
} 
