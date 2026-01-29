inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Sul street");
	set_long(BSS("You are walking along Sul street, close to the Stadium "+
		"Gate. You see a jewlery store to the northwest, and "+
		"Warriors Way to the northeast from here. There "+
		"is a hut to the south.\n"));

	add_exit(SUL_STR+"road6","west",0);
	add_exit(SLUM_D+"hut2","south",0);
	add_exit(SUL_STR+"road8","east",0);

}
