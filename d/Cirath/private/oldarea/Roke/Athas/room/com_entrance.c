inherit "/std/room";

#include "/d/Roke/common/defs.h"

create_room()	{

	set_short("Entrance to Athas, wizards entrance");
	set_long(BSS("You are standing on a sky, looking down towards "+
		"the mountains in the west of Athas, and the large desert on "+
		"the east side of it, with the huge city of Tyr. When you "+
		"now go east, you will end up at the pier of Athas' "+
		"west coast, with no way back.\n"));

	add_exit(SHORE_D+"pier1.c","east",0);

}
