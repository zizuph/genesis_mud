inherit "/std/room.c";
#include "lib_defs.h"

create_room()
{
	set_short("Secret Chamber");
	set_long(BS("This small chamber has the musty, dry smell "
	+ "of books, ancient tomes untouched for many decades. Volumes "
	+ "of every sort cram the bookshelves that "
	+ "line three walls from floor to ceiling. Against the fourth "
	+ "wall sits an antique writing desk, the kind with a cover "
	+ "that closes and locks over the desktop. This room seems to have survived better "
	+ "than the others; though the books look to be in the same poor shape "
	+ "as those throughout the library, the wooden shelves and desk seem sound.\n"));
	
	add_exit(LIBRARY+"library_13","southeast",0,1);

	add_item(({"books"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases.\n"));

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases, but most seem to begin with the letter 'Z'.\n"));
	
	add_item(({"bookshelf","bookshelves","shelves"}),BS("The many shelves are each "
	+ "stuffed with books, but you notice that all are in quite bad condition.\n"));

	add_prop(ROOM_I_INSIDE, 1);
	
	reset_room();
}

reset_room()
{
	object ob;
	if (!present("index"))
	{	ob = clone_object(LIBRARY+"index");
		ob->add_prop(OBJ_I_INVIS,1);
		ob->move(this_object());
	}
	if (!present("writing_desk"))
	{	ob = clone_object(LIBRARY+"writing_desk");
		ob->move(this_object());
	}
}
