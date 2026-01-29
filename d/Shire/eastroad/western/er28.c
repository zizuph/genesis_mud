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
 
   extraline = "North of here you see hills that seem "+
   "to go on forever. South of here you is a forest. "+
   "Going east the road heads towards Bree. West the "+
   "road heads towards the Brandywine river, past the "+
   "Barrow Downs.";
 
   add_item(({"hill","hills"}),"The hills are plain and "+
      "rocky. It looks very barren.\n");
   add_item("forest","The forest south of here is very dense. "+
      "You think that you can make your way through it though. "+
      "\n\nYou think that you can at least.\n");
   add_item(({"river","brandywine","brandywine river"}),"You "+
      "can't see the Brandywine river from here.\n");
   
   add_exit(EAST_R_DIR + "er27","west", "@@tree_west@@");   
   add_exit(EAST_R_DIR + "er29","east", "@@tree_east@@");
   
   add_exit(EAST_R_DIR + "er28n","north","@@tree_north@@",2,1);
   add_exit(EAST_R_DIR + "er28s","south","@@tree_south@@",2,1);
} 

void tree_east()
{
    tell_tree_fort("went east along the Great East road towards Bree.");
}

void tree_west()
{
    tell_tree_fort("went west down the Great East road and disappeared.");
}


void tree_north()
{
    tell_tree_fort("went north into the fields and disappeared.");
}

void tree_south()
{
    tell_tree_fort("went east along the Great East road towards Bree.");
}