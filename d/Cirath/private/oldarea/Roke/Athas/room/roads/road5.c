inherit "/d/Roke/Athas/room/roads/DESERT_ROAD.c";

#include "/d/Roke/defs.h"

void
create_desert()	{
	add_exit(SPEC_D+"maingate2","northeast",0,2);
	add_exit(ROAD_D+"road4","southwest",0,6);
}
