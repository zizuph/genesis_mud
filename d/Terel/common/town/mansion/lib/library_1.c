#include "lib_defs.h"

inherit "/d/Terel/common/town/mansion/lib/library_room.c";

void
create_room()
{
	set_short("Library");
	set_long(BS("You are in the library proper; around you is a "
	+ "maze of rickety bookshelves, each stuffed with " 
	+ "ancient books of every color and description. The air "
	+ "here is musty and dry, but a cool, moist breeze flows in from "
	+ "the battered door behind you.\n"));
	
	add_exit(LIBRARY+"library_2","north");
        add_exit(LIBRARY+"entrance","east",0,1);
	add_exit(LIBRARY+"library_3","south");
	add_exit(LIBRARY+"library_5","west");

	add_item(({"books","book"}),BS("There must be hundreds of tomes here, "
	+ "ranging from small pamphlets to massive volumes. Many seem to be "
	+ "in fine shape, but on closer inspection you realize that most "
	+ "are in fact unreadable...time has faded the ink as bookworms and "
	+ "mold have eaten the pages. You cannot even make out the titles "
	+ "on the spines in most cases, but most seem to begin with the letter "
	+ "'A'.\n"));

	add_prop(ROOM_I_INSIDE, 1);
}
