inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()	{
	set_short("Mountain side");
	set_long(BSS("You have walked onto a mountain cliff, leading "+
		"up to a narrow pass. You can only see the desert back "+
		"east from here.\n"));

	add_exit(ROAD_D+"road4","east",0,4);
	add_exit(ROAD_D+"pass3","west",0,2);

}

