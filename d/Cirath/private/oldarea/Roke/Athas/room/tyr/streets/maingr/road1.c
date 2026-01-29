inherit "/std/room";

#include "road.h"

create_room()	{

	set_short("Main Gate Road");
	set_long(BSS("You are now standing on the Main Gate Road, "+
		"which runs from here, to the Main Gate, "+
		"far west of here. You can see the Temple "+
		"of Tyr clearly to the east.\n"));

	add_exit(SQUA_D+"square1","east",0);
	add_exit(MGR_STR+"road2","west",0);

}

