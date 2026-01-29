inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()	{
	set_short("On pier");
	set_long(BSS(
		"You have landed on a small pier streaching out into the "+
		"Black Sea, on the west coast of Athas. To the east you "+
		"can only see the vast deserts of Athas, and to the west "+
		"you can see the end of the pier and far away you can see "+ 
		"the eastern shores of Atuan. There is a small sign here.\n"));

	add_item("sign","The sign reads: Ships to the Shire.\n");
	add_cmd_item("sign","read","The sign reads: Ships to the Shire.\n");
	add_exit(SHORE_D+"pier1","east" );
    "/d/Shire/common/greyhaven/pier2"->teleledningsanka();
}
