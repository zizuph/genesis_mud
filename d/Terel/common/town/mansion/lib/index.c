inherit "/std/object.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message)    break_string(message, 70)
#define TP              this_player
#define TO              this_object

object sc;

void 
init()
{
	::init();
	add_action("do_read","read");
	add_action("do_crumble","turn");
	add_action("do_crumble","close");
}

void
create_object()
{
	set_name(({"index","book"}));
	set_adj("handwritten");
	set_adj("ancient");
	set_long(BS("This book looks to be in truly awful condition; you "
	+ "doubt it would withstand even gentle handling. The text itself "
	+ "is handwritten in a fine, spidery script, much faded with age. "
	+ "You can barely make out the words on the open page before you, "
	+ "but what you see seems to be an index to the books in the library.\n"));
	
	add_prop(OBJ_M_NO_GET,BS("You don't think that picking the index "
	+ "up is such a good idea; the fragile book looks likely to "
	+ "disintegrate at the slightest touch.\n"));

	add_prop(OBJ_S_WIZINFO,BS("To add a book to the index: Place a file "
	+ "in the MANSION/library/books directory. The text of this file "
	+ "should be the text of your book, except that: "
	+ "1) The first line should be <title of the book>**<author of the book>, "
	+ "separated by two asteriks as indicated, and "
	+ "2) The second line should be the location of the book, i.e., "
	+ "library_#.c where # is the number of the room. Books could also "
	+ "be in the index room itself, I suppose, which is index_room.c.  " 
	+ "Players will have to search (probably many times) for your book "
	+ "BY ITS TITLE, so please go easy on them and use relatively simple "
	+ "titles--embed any fancy subtitles in the text itself. Also, for "
	+ "the sake of consistency, I'd like all of the authors to be Calathin "
	+ "names...not wizard names. So if you can handle the ego blow, let "
	+ "the author be some mortal from the mansion's long distant past, rather "
	+ "than using your own name. Thanks! \n"
	+ "		- Cedric (who can barely handle the ego blow himself :-)\n"));
    seteuid(getuid(this_object()));
}

int
do_crumble(string str)
{
	if (member_array(str,({"book","page","index"}))!=-1)
	{
		write(BS("You really don't think that is a good idea; the book "
		+ "looks fragile enough to crumble to dust at the merest brush "
		+ "of your hand.\n"));
		return 1;
	}
	else return 0;
}

int 
do_read(string str)
{
	string 	*book_list,*first_line, *title_words;
	string	title,author, newtitle;
	int 	i, j, size;

    if (query_prop(OBJ_I_INVIS))
    {
	notify_fail("Lots of books in here. Got a specific one in mind?\n");
	return 0;
    }
    if (str == "book" || str == "index")
    {
	seteuid(getuid(this_object()));
	say (BS(QCTNAME(TP()) + " studies the ancient handwritten book.\n"));
	book_list = get_dir(LIBRARY + "books/*.book");
	write(BS("The index lists " + sizeof(book_list) + " books by title "
	+ "and author:\n\n"));
	for (i=0;i<sizeof(book_list);i++)
	{	
		first_line = explode(read_file(LIBRARY + "books/"+book_list[i],1,1),"**");
		title = first_line[0];
		author = first_line[1];
		newtitle = "";
		size = sizeof(title_words = explode(title+" "," "));
		for (j=0;j<size;j++)
		    newtitle+=capitalize(title_words[j])+" ";
		    
		write(newtitle+"by "+author);
	}
	write("\n");
	return 1;
    }
    else
    {
	notify_fail("Read what?\n");
	return 0;
    }
}
