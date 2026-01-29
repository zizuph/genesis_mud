inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Main Gate Road");
	set_long(BSS("You are walking along the Main Gate Road, which "+
		"runs from the town square to the Main Gate of "+
		"Tyr. You can see buildings all around you, and "+
		"the road leads east and west.\n"));

	add_exit(MGR_STR+"road2","east",0);
	add_exit(MGR_STR+"road4","west",0);

}

