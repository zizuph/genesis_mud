inherit "/std/room";

#include "road.h"
object monster;

create_room()	{
	set_short("High Road");
	set_long(BSS("You are standing on High Road, with Diamond street leading "+
		"east, just passing the banquet hall. You notice a "+
		"castle just by the city walls. To the southwest you "+
		"can see a noble's house, and to the northeast you "+
		"see loads of houses of very good quality.\n"));

	add_exit(HGH_STR+"road2","southeast",0);
	add_exit(DIA_STR+"road3","east",0);
	add_exit(HGH_STR+"road4","northwest",0);

}
