inherit "/d/Roke/Athas/room/roads/DESERT_ROAD.c";

#include "/d/Roke/defs.h"

void
create_desert()	{
	add_exit(SHORE_D+"pier1","west",0,2);
	add_exit(ROAD_D+"road2","southeast",0,6);
}
