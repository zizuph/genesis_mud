#include "lib_defs.h"

inherit LIBRARY+"library_room.c";

void
create_room()
{
	set_short("Library");
	set_long(BS("You are at an intersection; narrow corridors "
	+ "of bookcases from every direction come together at this point. "
	+ "The air here is musty and dry, thick "
	+ "with the smell of ancient parchment and rotting wood.\n"));
	
	add_exit(LIBRARY+"library_9","south");
	add_exit(LIBRARY+"library_5","east");
	add_exit(LIBRARY+"library_11","west");
	add_exit(LIBRARY+"library_7","north");

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases, but most seem to begin with the letters 'K' and 'L'.\n"));

	add_item(({"bookcase","shelf","shelves","bookcases"}),BS("These rickety old bookcases seem "
	+ "precariously overloaded with books, but somehow they all remain upright.\n"));

	add_prop(ROOM_I_INSIDE, 1);
	
}
