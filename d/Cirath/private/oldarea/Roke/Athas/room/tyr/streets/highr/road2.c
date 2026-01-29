inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("High Road");
	set_long(BSS("This is the High Road, northwest of the town square, "+
		"leading into the nobles' quarters. To the east you "+
		"see the west walls to the banquet hall, and to the "+
		"west you see one of the many houses belonging to "+
		"nobles in the area.\n"));

	add_exit(HGH_STR+"road1","southeast",0);
	add_exit(HGH_STR+"road3","northwest",0);

}

