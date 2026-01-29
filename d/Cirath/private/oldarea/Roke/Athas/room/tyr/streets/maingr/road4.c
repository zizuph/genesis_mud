inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Main Gate Road");
	set_long(BSS("You are walking along Main Gate Road, which runs from "+
		"the Main Gate of Tyr to the town square and the "+
		"temple. The Sword Street is leading south here, "+
		"while the Main Gate Road runs east and west.\n"));

	add_exit(MGR_STR+"road3","east",0);
	add_exit(SWO_STR+"road1","south",0);
	add_exit(MGR_STR+"road5","west",0);

}

