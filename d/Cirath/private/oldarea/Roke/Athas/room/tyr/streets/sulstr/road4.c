inherit "/std/room";

#include "road.h"


create_room()	{
	set_short("Bend in Sul street");
	set_long(BSS("You have reached a bend in Sul street, from here the "+
		"street changes directions, and leads northwest and "+
		"east. There is a tavern to the south of here.\n"));

	add_exit(SUL_STR+"road3","northwest",0);
	add_exit(INNS_D+"tavern1","south",0);
	add_exit(SUL_STR+"road5","east",0);

}

