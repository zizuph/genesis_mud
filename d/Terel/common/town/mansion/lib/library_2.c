#include "lib_defs.h"

inherit LIBRARY+"library_room.c";

void
create_room()
{
  object sc;
	set_short("Library");
	set_long(BS("You are in a narrow alcove, formed by a rickety "
	+ "bookcase to the west and deteriorating bookshelves that line the walls "
	+ "to the north and east. The air here is musty and dry, thick "
	+ "with the smell of ancient parchment and rotting wood.\n"));
	
	add_exit(LIBRARY+"library_1","south");

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
+ "on the spines in most cases, but most seem to begin with the letters "
	+ "'B' and 'C'.\n"));

	add_item(({"bookcase"}),BS("This rickety old bookcase seems "
	+ "precariously overloaded with books, but somehow it still stands.\n"));
	add_item(({"bookshelves","shelf","shelves"}),BS("These rotting bookshelves line the walls from floor "
	+ "to ceiling, each filled with ancient texts of every kind.\n"));

	add_prop(ROOM_I_INSIDE, 1);
	
  seteuid(getuid());
  sc = clone_object("/d/Terel/mecien/valley/guild/quest/scroll");
   sc->move(this_object());
}
