#include "lib_defs.h"

inherit LIBRARY+"library_room.c";

void
create_room()
{
	set_short("Library");
	set_long(BS("You are in a narrow corner, formed by a rickety "
	+ "bookcase to the west and a decaying set of bookshelves that line "
	+ "the northern wall of the room. To your east is a small alcove. "
	+ "The air here is musty and dry, thick "
	+ "with the smell of ancient parchment and rotting wood.\n"));
	
	add_exit(LIBRARY+"library_8","south");
	add_exit(LIBRARY+"library_6","east");

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases, but most seem to begin with the letters "
	+ "'I' and 'J'.\n"));

	add_item(({"bookcase"}),BS("This rickety old bookcase seems "
	+ "precariously overloaded with books, but somehow it still stands.\n"));
	add_item(({"bookshelves","shelf","shelves"}),BS("These rotting bookshelves line the northern wall from floor "
	+ "to ceiling, filled with ancient texts of every kind.\n"));

	add_prop(ROOM_I_INSIDE, 1);
	
}
