#include "lib_defs.h"

inherit LIBRARY+"library_room.c";

void
create_room()
{
	set_short("Library");
	set_long(BS("You are at the far west end of the library. "
	+ "Little corridors of bookcases branch off north, south, "
	+ "and east here, and a decaying set of bookshelves lines "
	+ "the western wall. "
	+ "The air here is musty and dry, thick "
	+ "with the smell of ancient parchment and rotting wood.\n"));
	
	add_exit(LIBRARY+"library_13","north");
	add_exit(LIBRARY+"library_15","south");
	add_exit(LIBRARY+"library_11","east");

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases, but most seem to begin with the letters 'U', 'V', and 'W'.\n"));

	add_item(({"bookshelves","shelf","shelves"}),BS("These rotting bookshelves line the western wall from floor "
	+ "to ceiling, stuffed with ancient texts of every kind.\n"));

	add_prop(ROOM_I_INSIDE, 1);
	
}
