inherit "/std/room";

#include "road.h"

create_room()	{
	set_short("Temple Roads");
	set_long(BSS("You are walking along Temple Road, north of the Temple "+
		"of Tyr, southeast of here you see the gladiatorial "+
		"arena, and to the northeast you see the slave pits. "+
		"Far to the east you can also see a huge tower, while "+
		"to the west you see the town square.\n"));

 add_exit(TEM_STR+"road1","west");
 add_exit(TEM_STR+"road3","east");

}

