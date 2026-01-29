inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("High Road");
	set_long(BSS("This road, known as High Road, leads from the town square "+
		"to the nobles' quarters. To the east you can see "+
		"the west wall of the nobles banquet hall, and to the "+
		"west you can see the home of some noble.\n"));

	add_item(({"banquett hall","hall"}), BSS(
		"You cannot see the banquett hall from here, you can "+
		"only see the western wall of it.\n"));

	add_item(({"wall"}), BSS(
		"The walls are made of yellow sandstone, the only "+
		"material usefull to build with, that you find here "+
		"in the desert.\n"));

	add_item(({"house","nobles house"}),BSS(
		"This is a rather large house, typical for the "+
		"noble families of Tyr. The house contains of two floors "+
		"and the walls are made of sandstone.\n"));

	add_exit(SQUA_D+"square1","south",0);
	add_exit(HGH_STR+"road2","northwest",0);

}

