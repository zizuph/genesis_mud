/* The Great Library of Arcoron Domain Room.
 * Also stolen from the Rangers Guild, many thanks to Elessar for
 * letting me make use of it.
 * Made by Elessar, April 1992.
 */

inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include "/d/City/defs.h"
#define DIR "/d/City/chaos/library/domain/books/"
#define BOOK_LIST "/d/City/chaos/library/domain/books/arcbooks"
#define MORE_OBJ "/std/board/board_more"
#define PATH "/d/City/chaos/library/"

string *books, *authors;

create_room()
{
   if(!books)
	books = ({});
  set_short("The Domain Room");
  set_long("This is a much smaller room with only one small bookshelf "+
	"located on the east wall.  It has several different looking "+
	"books on it.  There are several chairs in the room and seated "+
	"in one of them is a rather old looking man, quietly rocking "+
	"back and forth near the entrance.  His purpose is unclear but "+
	"it doesn't look like he will let you leave the room with a book.\n");
  add_prop(ROOM_I_LIGHT,1);
  add_prop(ROOM_I_INSIDE,1);
  add_exit(PATH + "library","west","@@check_for_book",0);
  add_item("shelf","@@exa_shelves");
  add_item("avenir","This tattered and weathered book looks like it has "+
	"seen better days.  It's spine is bound with three rusty iron "+
	"rings and the scarlet leather cover is embossed with the Great "+
	"Seal of the Lord High Commissioner.  Binding the books closed "+
	"is a wax seal depicting a pair of slanting eyes with a rod and "+
	"flail crossed beneath them.\n");
  add_item("calia","This book is bound in a fine black leather.  On its "+
	"cover in silver ink is a shimmering crystal palace.\n");
  add_item(({"librarian","old man","man"}),"The old guy looks to be of "+ 
	"human descent, but the ravages of time make it difficult to be "+
	"certain.  It's possible he sits here to make sure that nobody "+
	"leaves with any books.  Of course, it looks like he's been "+
	"sitting here longer than most of the books.\n");
}

exa_shelves()
{
  return "The shelf contians several different looking books.  Each one "+ 
	"has a name printed on it's binding.  The names are:\n"+
	"Arcoron, Avenir, Calia, Emerald, Gondor, Immortal, Kalad, "+
	"Krynn, Liwitch, Rhovanion, Roke, Shire, Terel.\n";
}

check_for_books()
{
  if (present("Arcoron_Library_Book",TP))
    {
      write("The old man blocks you with his cane, and says: Give me that "+ 
	"book first!\n");
      say(QCTNAME(TP)+" tries to leave with a book, but is stopped.\n",TP);
      return 1;
    }
  return 0;
}

init()
{
  ::init();
  add_action("no_say","say");
  add_action("no_say","'",1);
  add_action("no_say","scream");
  add_action("no_say","rsay");
  add_action("no_say","shout");
  add_action("no_say","grsay");
  add_action("no_say","laugh");
  add_action("no_say","sing");  
  add_action("read_book","read");
  add_action("add_book","newbook");
  add_action("remove_book","banbook");
  add_action("list_all_books","allbooks");
  add_action("add_author","newauthor");
  add_action("remove_author","banauthor");
  add_action("list_all_authors","allauthors");
}

no_say()
{
  string vb;
  vb = query_verb();

  if(vb == "say" || vb == "grsay" || vb == "rsay" || explode(vb,"")[0] == "'")
    vb = "speak";
  write("You are about to open your mouth to "+vb+" when you happen to\n"+
	"look at the old man, his stern eyes are staring right at you.\n"+
	"Maybe whispering would be more appropriate.\n");
  return 1;
}

read_book(string book)
{
  if (!book) 
	{
	notify_fail("Read what?\n");
    	return 0;
	}
  if (present(book,TP)) return 0;
  if (book_exists(book))
    {
      write("You read the book titled "+capitalize(book)+".\n");
      say(QCTNAME(TP)+" reads a book from the shelves.\n",TP);
      book = lower_case(book);
      clone_object(MORE_OBJ)->more(DIR+book+".hst", 2);
      return 1;
    }
  write("You don't see that book here.\n");
  return 1;
}

borrow_book(string title)
{
  object book;
  if (!title || !book_exists(title))
    {
      write("Borrow what book?\n");
      return 1;
    }
  write("You take the book titled "+title+" from the shelves.\n");
  say(QCTNAME(TP)+" takes a book from the shelves.\n",TP);
  book = clone_object(DIR+"book");
  book->set_book_title(title+".txt");
  book->move(TP);
  return 1;
}

int wiz(object player)
{
  if(player->query_wiz_level() >= 15)
    return 1;
  return 0;
}

book_exists(string booktitle)
{
  int n;
  if (!booktitle) return 0;
  booktitle = capitalize(lower_case(booktitle));
  restore_object(BOOK_LIST);
  while (n<sizeof(books))
    {
      if (booktitle == books[n]) return 1;
      n++;
    }
  return 0;
}

add_book(string book)
{
  if (!wiz(TP)) return 0;
  if (book_exists(book)) 
    {
      write("The librarian says: That book is already in our shelves, "+
	"TP->query_cap_name().\n");
      return 1;
    }
  book = capitalize(lower_case(book));
  books = books + ({book});
  save_object(BOOK_LIST);
  write("You put a book titled "+book+" in the shelves.\n");
  say(QCTNAME(TP)+" puts a new book in the shelves.\n",TP);
  if (TP->query_cap_name()!="Chaos") 
    write("Mail Chaos about the title you added, please!\n");
  return 1;
}

query_title_list()
{
  string title_list;
  int n;
  if (!sizeof(books)) return "No books available.\n";
  title_list = "Currently these titles are available in the Great Library: ";
  while (n<sizeof(books)-1)
    {
      title_list = title_list+books[n]+", ";
      n++;
    }
  title_list = title_list+books[n]+".\n";
  return (title_list);
}

list_all_books()
{
  if (!wiz(TP)) return 0;
  write(query_title_list());
  return 1;
}

remove_book(string book)
{
  int n;
  if (!wiz(TP)) return 0;
  if (!book_exists(book))
    {
      write("That book is not in the shelves!\n");
      return 1;
    }
  book = capitalize(lower_case(book));
  while (n<sizeof(books))
    {
      if (book == books[n]) {
	books = exclude_array(books,n,n);
	write("You remove the book titled "+book+" from the shelves.\n");
	say(QCTNAME(TP)+" removes a book from the shelves.\n",TP);
	save_object(BOOK_LIST);
	return 1;
      }
      n++;
    }
  write("The book didn't exist afterall.\n");
  return 1;
}

author_exists(string author)
{
  int n;
  if (!author) return 0;
  author = lower_case(author);
  while (n<sizeof(authors))
  {
    if (author == authors[n]) 
      return 1;
    n++;
  }
  return 0;
}

string query_author_list()
{
  string author_list;
  int n;
  if (!sizeof(authors)) return "No authors named.\n";
  author_list = "";
  while (n<sizeof(authors)-1)
    {
      author_list += CAP(authors[n])+", ";
      n++;
    }
  author_list += CAP(authors[n])+".";
  author_list = ("Currently these mortals have access to the Great "+ 
	"Library of Arcoron:") +
    	(author_list);

  return (author_list);
}

int list_all_authors()
{
  if(!wiz(TP))
    return 0;
  write(query_author_list());
  return 1;
}
  
add_author(string author)
{
  if (!wiz(TP)) return 0;
  author = lower_case(author);
  if(author_exists(author))
  {
    write("The librarian says: That mortal has already access "+
	"to the library, TP->query_cap_name().\n");
      return 1;
  }
  if(!SECURITY->finger_player(author) || SECURITY->query_wiz_level(author))
  {
    write("The librarian says: There is no mortal with that name, "+ 
	"TP->query_cap_name()\n");
      return 1;
  }
  if(!sizeof(authors))
    authors = ({author});
  else
    authors = authors + ({author});
  save_object(BOOK_LIST);
  write("You enable the mortal "+CAP(author)+" to enter the library.\n");
  return 1;
}

int remove_author(string author)
{
  int n;
  if (!wiz(TP)) return 0;
  author = lower_case(author);
  if (!author_exists(author))
  {
    write("That mortal has no access to the library!\n");
    return 1;
  }
  while (n<sizeof(authors))
  {
    if (author == authors[n]) 
    {
      authors = exclude_array(authors,n,n);
      write("You remove "+CAP(author)+" from the list of mortals "+
	"which have access to the library.\n");
      save_object(BOOK_LIST);
      return 1;
    }
    n++;
  }
  write("The author didn't have access afterall.\n");
  return 1;
}

