inherit "/std/room.c";

#include "/d/Terel/common/terel_defs.h"
#include <stdproperties.h>
#include <macros.h>

#define BS(message) 	break_string(message,70)
#define TP              this_player
#define TO              this_object
#pragma save_binary

void
init()
{
	::init();
	add_action("do_search","search");
	add_action("do_get","get");
}

int
do_get(string str)
{
	object ob;

    if (str == "book")
    {
	ob = clone_object(LIBRARY+"book.c");
	write(BS("You study the vast quantity of books before "
	+ "you, and arbitrarily pick a "+ob->query_name()+" from "
	+ "the shelves.\n"));
	say(BS(QCTNAME(TP())+" picks a "+ob->query_name()+" from the shelves, seemingly at random.\n"));
	if (ob->move(TP()))
	{
		write("You drop the "+ob->query_name()+" on the floor.\n");
		ob->move(environment());
	}
	return 1;
    }
    else
    {
	return 0;
    }
}

int
do_search(string str)
{
	object 		ob;
	string 		*command_line,*book_dir,*title_list;
	string		*first_line;
	string		book_name;
	int 		i,found_flag;

	found_flag = -1;
    if (member_array(str,({"bookcase","bookshelves","bookshelf","shelves","shelf","books","book"})) != -1)
	{
		write(BS("There are so many books here...perhaps if "
		+ "you searched for a specific title?\n"));
		return 1;
	}
    else
    {   if (!str)
		return 0;
	command_line = explode(str," ");
	if (command_line[0] != "for")
		return 0;
	else
	{
		book_name = extract(str,4);
		book_dir = get_dir(LIBRARY+"books/*.book");
		for (i=0;i<sizeof(book_dir);i++)
		{
			first_line =  explode(read_file(LIBRARY+"books/"+book_dir[i],1,1),"**");
			if (first_line[0] == book_name 
			    && (file_name(environment(TP()))+".c")==
				extract(LIBRARY+read_file(LIBRARY+"books/"+book_dir[i],2,1),0,
				strlen(LIBRARY+read_file(LIBRARY+"books/"+book_dir[i],2,1))-2))
			{
				found_flag = i;
				write("You find a copy!\n");
                                break;
			}
		}
		if (found_flag!=-1)
		{
			ob = clone_object(LIBRARY+"book.c");
			write("You pick a "+ob->query_name()+" from the shelves.\n");
			say(BS(QCTNAME(TP())+" glances over the books, and picks out a "+ob->query_name()+".\n"));
			ob->set_text(book_dir[found_flag]);
			if (ob->move(TP()))
			{
				write("You drop the "+ob->query_name()+" on the floor.\n");
				ob->move(environment());
			}
		}
		else
		{
			write(BS("You glance over the books, but don't find that title. "
			+ "Not here, at least...\n"));
			say(BS(QCTNAME(TP())+ " studies the books, but doesn't seem to find what "
			+ TP()->query_pronoun() + " is looking for.\n"));
		}
		return 1;
	}
    }
}
