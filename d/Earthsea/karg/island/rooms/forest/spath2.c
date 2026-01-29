#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void create_island_room()
{
 set_short("Small path in the forest");
 set_long("On the small , almost invisable path through the forest."+
   "Forest seems very dense here , trees from both sides of path are "+
   "old and sturdy. Path continues to south and southeast.\n");

 add_exit(FROOMS+"/@@random_forest","north");
 add_exit(FROOMS+"/@@random_forest","northeast");
 add_exit(FROOMS+"/@@random_forest","west");
 add_exit(FROOMS+"/@@random_forest","east");
 add_exit(FROOMS+"/@@random_forest","southwest");
 add_exit(FROOMS+"/@@random_forest","northwest");
 add_exit(FROOMS+"/spath1","south");
 add_exit(FROOMS+"/spath3","southeast");

 add_item(({"tree","trees","forest"}),
   "The trees on the both sides make the path so "+
   "narrow that it is hardly seen. You have an "+
   "instant feeling of beeing watched.\n\n");

 add_item(({"ground","path","track"}),
   "The track is crossed by gnarled roots here and "+
   "there. False trails lead in every direction. "+
   "You can see animal tracks, some of them quite "+
   "fresh.\n\n");
}

string random_forest()
{
 write("Oh, no! You are lost now! You can wander here FOREVER!\n\n");
 return "forest"+random(20);
}


