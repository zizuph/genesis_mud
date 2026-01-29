inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Main Gate Road");
	set_long(BSS("You are walking along the Main Gate Road, which "+
		"runs between the Main Gate of Tyr, and the town "+
		"square. There is a post office to the north.\n"));

	add_exit(MGR_STR+"road5","east",0);
	add_exit(COMM_D+"post","north",0);
	add_exit(MGR_STR+"road7","west",0);

}

