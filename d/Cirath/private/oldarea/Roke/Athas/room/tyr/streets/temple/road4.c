inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Temple Roads");
	set_long(BSS("You are standing at the end of Temple Road, just "+
		"north of the gladiatorial arena. To the east you see "+
		"a huge golden tower, and northwest you see the slave "+
		"pits. Further southwest you can see the temple, and "+
		"far west you see the town square.\n"));

	add_exit(TEM_STR+"road3","west",0);
	add_exit(GLA_CIR+"xxx","east","@@closed");

}

closed()	{
   write("This place is currently not open for tourists.\n");
	return 1;
}

