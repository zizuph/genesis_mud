#pragma save_binary
#pragma strict_types

#include "local.h"

inherit EAST_ROAD; 
 
#define BLACKRIDER_ROOM		"/d/Gondor/morgul/blackrider"
 
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
	"city of Bree. The road continues west to the Brandywine "+
	"river. You see a building along the road before the Bridge "+
	"of Stonebows.";
 
	add_item("forest","The forest does not seem that hard to "+
		"move through. You see the forest thinning out in the "+
		"west because of the Brandywine river. You notice that "+
		"where the forest thinns out at a bank of the river.\n");
	add_item(({"hill","hills"}),"The hills are non-ending. "+
		"To the northwest you see the Brandywine river meet "+
		"up with the hills.");
	add_item(({"river","brandywine","brandywine river"}),
		"The Brandywine Bridge is west of here. The river "+
		"looks deep cold wet and it also looks as if it is moving "+
		"swiftly. At least that is what it seems like from here.\n");
	add_item(({"bridge","stonebows","bridge of stonebows"}),"You "+
		"cannot make much detail out on the bridge. You do notice a "+
		"building between you and the bridge though.\n");
	add_item("building","The building is a little ways down the road "+
		"looks like it may be an inn. Perchance you will stop there and "+
		"get some food or drink.\n");
 
   add_exit(EAST_R_DIR + "er22","west",0,2);
   add_exit(EAST_R_DIR + "er24","east",0,2);
 
   add_exit(EAST_R_DIR + "er23n","north","@@north_msg@@",2,1);
   add_exit(EAST_R_DIR + "er23s","south","@@south_msg@@",2,1);

   BLACKRIDER_ROOM->load_me();
}




