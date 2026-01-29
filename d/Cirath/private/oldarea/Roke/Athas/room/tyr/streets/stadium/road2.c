inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Stadium Road");
	set_long(BSS("You are walking along the Stadium Road, just south of the "+
		"temple. To the northeast you can see the gladiatorial "+
		"arena, and to the southeast you see the Warriors Way. "+
		"Farther east you can see a large tower.\n"));

	add_exit(STA_STR+"road1","west",0);
	add_exit(STA_STR+"road3","east",0);

}

