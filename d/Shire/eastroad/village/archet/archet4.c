#include "defs.h"
inherit ER_DIR +"eroad";

create_room()
{
	area = "far from";
	areaname = "Bree";
	land = "Eriador";
	areatype = 7;
	treetype = "oak";
	areadesc = "path";
	
	extraline = 
		"The path seems to go on for a long distance eastwards, but "+
		"a bit west of here an opening in the forest can be spotted. Green "+
		"trees surround the road, and many strange noises can be heard. "+
		"The forest is thick and appears impenetratable. Grass cover the "+
		"sides of the road.";
	ITEM(({"path", "road"}),"The road is dusty even though it is in the middle "+
		"of a forest. It must be used a lot, because grass haven't started "+
		"growing on it yet.\n");
	ITEM("opening", "A bright opening can be seen a bit west, perhaps the edge "+
		"of the forest?\n");
	ITEM("noises", "Birds is singing and flys hum all over the place.\n");
	add_exit(ARCHET_DIR +"archet3", "west", 0);
	add_exit(ARCHET_DIR +"archet5", "east", 0);
	make_the_room();
}

