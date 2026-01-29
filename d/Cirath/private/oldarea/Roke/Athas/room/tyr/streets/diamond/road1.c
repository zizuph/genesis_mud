inherit "/std/room";

#include "road.h"

#define XXX "/d/Roke/Athas"

create_room()	{
	set_short("Diamond Street");
	set_long(BSS("You are standing on the east end of Diamond street, just "+
		"south of a castle. You see a house with a lovely "+
		"garden outside to the southeast, and to the "+
		"southwest you can see the banquett hall where the "+
		"nobles and the king have their celebrations. Further "+
		"west you can see many houses of high quality.\n"));

	add_exit(DIA_STR+"road2","west",0);
	add_exit(XXX+"xxx","north","@@closed");
	add_exit(PAL_STR+"street3","south",0);

}

closed()	{
	write(BSS("Due to a construction falure by the builder, this castle "+
		"is closed for maintainence. There could be danger "+
		"for your life if we let you in. We hope to be "+
		"finished with the repears in a few days.\n"));
	return 1;
}

