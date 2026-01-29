inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Merchant's Road");
	set_long(BSS("You are walking down the Merchant road, which leads from "+
		"the town square in Tyr, south to the market. "+
		"There is a hut just to the east from here, "+
		"while the road leads farther south.\n"));

	add_exit(SQUA_D+"square7","north",0);
	add_exit(MER_STR+"road2","south",0);
	add_exit(SLUM_D+"hut3","east",0);

}

