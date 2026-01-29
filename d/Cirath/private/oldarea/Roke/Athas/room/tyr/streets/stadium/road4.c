inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Stadium Road");
	set_long(BSS("You are at the end of Stadium Road, just "+
		"south of the gladiatorial stadium. You see a "+
		"huge tower to the east, clad with golden plates "+
		"and silver roof. To the southwest you can see the "+
		"Warriors Way, and to the northwest you see the "+
		"temple.\n"));

	add_exit(STA_STR+"road3","west",0);
	add_exit(GLA_CIR+"xxx","east","@@closed");

}

closed()	{
	write(BSS("Sorry, but this area is closed to tourists.\n"));
	return 1;
}

