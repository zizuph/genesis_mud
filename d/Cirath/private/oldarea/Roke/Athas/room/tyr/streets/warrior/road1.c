inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Warrior's Way");
	set_long(BSS("This street between the Gladiator Stadium and the "+
		"Stadium Gate, down by Sul Street. The road is named "+
		"Warriors Way, and from here you can see the "+
		"arena directly north of here, a part of the Kings Garden "+
		"to the east, while the Gladiator guild is "+
		"southwest of here.\n"));

   add_exit(STA_STR+"road3","north");
   add_exit(WAR_STR+"road2","south");

}
