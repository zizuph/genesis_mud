inherit "/d/Roke/Athas/room/roads/DESERT_ROAD.c";

#include "/d/Roke/defs.h"

void
create_desert()	{
	add_exit(ROAD_D+"ent_pass","northeast",0,4);
	add_exit(ROAD_D+"road2","west",0,6);
}
