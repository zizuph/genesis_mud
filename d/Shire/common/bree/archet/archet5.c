#include "defs.h"
inherit ER_DIR +"eroad";

create_room()
{
	area = "far";
	areadesc = "path";
	areaname = "Bree";
	land = "Eriador";
	areatype = 7;
	treetype = "oak";
	
	extraline = "The road is paved and goes in a west-east direction. On "+
		"both sides of the road the forest is, and it seems like it is "+
		"getting closer to the road the further inwards one moves.";

	add_exit(ARCHET_DIR +"archet4", "west", 0);
	add_exit(ARCHET_DIR +"archet6", "east", 0);
	make_the_room();
}

