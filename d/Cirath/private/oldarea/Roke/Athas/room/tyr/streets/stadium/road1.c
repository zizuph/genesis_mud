inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Stadium Road");
	set_long(BSS("This is the Stadium Road, running south of the temple and "+
		"gladiatorial arena. To the west you can see the "+
		"town square, and to the north you see the walls "+
		"of the temple. Farther northeast you can see the "+
		"arena walls, and to the east you see a large tower.\n"));

	add_exit(SQUA_D+"square9","west",0);
	add_exit(STA_STR+"road2","east",0);

}

