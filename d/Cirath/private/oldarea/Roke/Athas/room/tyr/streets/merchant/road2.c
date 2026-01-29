inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Merchant's Road");
	set_long(BSS("You are standing on the south end of Merchant road, "+
		"just north of the market. Farther north you will "+
		"come to the town square, while the market south of "+
		"here could be a nice place to buy supplies for "+
		"travelling in the desert.\n"));

	add_exit(MER_STR+"road1","north",0);
	add_exit(SQUA_D+"mark1","south",0);

}

