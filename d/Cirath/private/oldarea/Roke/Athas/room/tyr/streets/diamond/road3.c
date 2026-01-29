inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Diamond Street");
	set_long(BSS("You are standing on the west end of Diamond street, "+
		"just northwest of the banquet hall. You can see the "+
		"High Road just west of here, and beyond it, you see "+
		"many high class houses.\n"));

	add_exit(DIA_STR+"road2","east",0);
	add_exit(HGH_STR+"road3","west",0);

}

