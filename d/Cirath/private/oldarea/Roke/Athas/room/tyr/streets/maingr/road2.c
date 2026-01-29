inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Main Gate Road");
	set_long(BSS("You are on the Main Gate Road, which runs from "+
		"the town square to the Main Gate. Here you can "+
		"vaguely see the Temple of Tyr to the far east "+
		"and Shield Street to the south.\n"));

	add_exit(MGR_STR+"road1","east",0);
   add_exit(SHI_STR+"road1","south");
   add_exit(MGR_STR+"road3","west");

}

