#include "lib_defs.h"
inherit "/d/Terel/common/town/mansion/lib/library_room.c";


void
create_room()
{
	set_short("Library");
	set_long(BS("You are in a maze of twisty little bookcases, all alike; "
	+ "there is a rickety bookcase to the south and corridors formed by "
	+ "similar bookcases branch off to the north, east, and west. "
	+ "The air here is musty and dry, thick "
	+ "with the smell of ancient parchment and rotting wood.\n"));
	
	add_exit(LIBRARY+"library_14","west");
	add_exit(LIBRARY+"library_8","east");
	add_exit(LIBRARY+"library_12","north");

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases, but most seem to begin with the letter 'P'.\n"));

	add_item(({"bookcase"}),BS("This rickety old bookcase seems "
	+ "precariously overloaded with books, but somehow it still stands.\n"));
	add_item(({"bookshelves","shelf","shelves"}),BS("These rotting bookshelves line the walls from floor "
	+ "to ceiling, each filled with ancient texts of every kind.\n"));

	add_prop(ROOM_I_INSIDE, 1);
	
}
