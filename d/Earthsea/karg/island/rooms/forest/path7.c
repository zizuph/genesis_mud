#include <macros.h>
#include <stdproperties.h>
#include <ss_types.h>
#include "../../std/defs.h"

inherit ISL_DIR+"/std/room";

void
create_island_room()
{
        set_short("Path in the forest");
	set_long("You are on a path leading through dark forest. "+
		 "The forest on the both sides of the path is "+
		 "so dense that you do not dare to step aside. "+
		 "You hear threatening growls from the "+
		 "undergrowth. The forest seems to be wild "+
		 "but not uninhabited. The path comes from the "+
		 "north and bends slightly to southeast.\n\n");
	
	add_exit(FROOMS+"/@@random_forest","south");
	add_exit(FROOMS+"/@@random_forest","northeast");
	add_exit(FROOMS+"/@@random_forest","west");
	add_exit(FROOMS+"/@@random_forest","east");
	add_exit(FROOMS+"/@@random_forest","northwest");
	add_exit(FROOMS+"/@@random_forest","southwest");
	add_exit(FROOMS+"/path8","southeast");
	add_exit(FROOMS+"/path6","north");
	
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

string
random_forest()
{
	write("Oh, no! You are lost now! You can wander here"+
	      " FOREVER!\n\n");
	return "forest"+random(20);
}

