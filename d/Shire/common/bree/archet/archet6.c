#include "defs.h"
inherit ER_DIR +"eroad";

create_room()
{
	area = "far";
	areaname = "Bree";
	areatype = 7;
	areadesc = "dark path";
	treetype = "oak";
	land = "Eriador";
	
	extraline = "There is nothing but trees and shrubs around here, but a "+
		"road cut into the forest and leads southwest from here. It is a "+
		"smaller path then the main east-west, and is not paved.";
	ITEM("shrubs", "Young trees, or shrubs stand at the side of the road. "+
		"They are only about 4-6 feet tall.\n");
	ITEM("road", "A smaller road leads southwest, into the forest, and the "+
		"main road goes west-east.\n");
	add_exit(ARCHET_DIR +"archet5", "west", 0);
	add_exit(ARCHET_DIR +"archet7", "east", 0, 2);
	add_exit(ARCHET_DIR +"arch7_2", "southwest", 0, 1);
	make_the_room();


