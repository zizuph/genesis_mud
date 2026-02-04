#include "lib_defs.h"
inherit LIBRARY+"library_room.c";


void
create_room()
{
	set_short("Library");
	set_long(BS("You are in a narrow alcove, formed by a rickety "
	+ "bookcase to the east and deteriorating bookshelves that line the walls "
	+ "to the south and west. The air here is musty and dry, thick "
	+ "with the smell of ancient parchment and rotting wood.\n"));
		
	add_exit(LIBRARY+"library_14","north");

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases, but most seem to begin with the letters 'X' and 'Y'.\n"));

	add_item(({"bookcase"}),BS("These rickety old bookcases seem "
	+ "precariously overloaded with books, but somehow they all remain upright.\n"));
	add_item(({"bookshelves","shelf","shelves"}),BS("These rotting bookshelves line the walls from floor "
	+ "to ceiling, each filled with ancient texts of every kind.\n"));

	add_prop(ROOM_I_INSIDE, 1);
	
}
