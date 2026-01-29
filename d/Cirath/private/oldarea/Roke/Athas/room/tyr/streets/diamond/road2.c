inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Diamond Street");
	set_long(BSS("You are walking along the Diamond street, in the middle of "+
		"the noble areas. To the south you see the entrance "+
		"to the nobles' banquet hall, and to the northeast "+
		"you see a small castle, built close up to the city "+
		"wall. You can see many high quality houses to the "+
		"west, and a single house to the northwest.\n"));

	add_exit(DIA_STR+"road1","east",0);
	add_exit(DIA_STR+"road3","west",0);
	add_exit(SHOP_D+"banquett","south","@@closed");

}

closed()	{
	write(BSS("Sorry, but the banquet hall is closed for repairs.\n"));
	return 1;
}

