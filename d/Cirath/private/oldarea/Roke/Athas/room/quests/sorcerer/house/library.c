inherit "/d/Roke/gresolle/open/library";

#include <stdproperties.h>
#include "/d/Roke/common/defs.h"

create_library()	{

	set_short("Library");
	set_long(BSS("You are standing in a large room, looking at some "+
		"bookshelves, you guess it is a library. The bookshelves "+
		"contain many thousands of books, and you wonder how "+
		"anyone could manage to collect so many books. You can see a "+
		"sign on the wall, and a study east.\n"));

	set_lib_name("Pandoras Library");
	set_save_path(BOOKS+"sor_books");

	lib_exit(HOUS_D+"livingroom","west");
	lib_exit(HOUS_D+"study","east");

	add_item(({"book","books"}), BSS(
		"There are so many books that you cannot decide which to look "+
		"at, but you can see a list hanging on one side of the shelf "+
		"including all the books in the library. Type 'list' to look "+
		"at it.\n"));

	add_item(({"shelf","shelves"}),BSS(
		"The shelves are filled with books.\n"));

	add_item("list","Type 'list' to read the list.\n");

	add_cmd_item("sign","read","@@sign");

	add_item("sign",BSS(
		"The sign is a plaque, nailed to the wall, and you can "+
		"see some writing on it. Looking closer at it tells you "+
		"that it is made of some kind of metal, and that it is "+
		"securely fastened to the wall.\n"));


}

sign()	{

	return BSS("This library is a collection of books, that I, "+
		"Templar Pandora, have collected through the years "+
		"I have lived. You can <borrow> the books to read, but "+
		"you will have to <return> them before "+
		"you leave. <list> will give you a list of which books "+
		"or texts that are presently located in the library.\n");
}
