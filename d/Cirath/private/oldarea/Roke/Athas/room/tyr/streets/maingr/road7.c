inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Main Gate Road");
	set_long(BSS("You are walking along the Main Gate Road, which runs "+
		"between the Main Gate and the town square. The "+
		"Main Gate is just west of here, and to the northeast "+
		"see a post office.\n"));

	add_exit(MGR_STR+"road6","east",0);
	add_exit(SPEC_D+"maingate","west",0);

}

