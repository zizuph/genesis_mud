/* The Great Library of Arcoron.
 * This room is stolen from the Rangers Guild, many thanks to Elessar for
 * letting me make use of it.
 * Made by Elessar, April 1992.
 */

inherit "/std/room.c";
#include <stdproperties.h>
#include <macros.h>
#include <std.h>
#include "/d/City/defs.h"
#define DIR "/d/City/chaos/open/library/books/"
#define BOOK_LIST "/d/City/chaos/open/library/books/arcbooks"
#define MORE_OBJ "/std/board/board_more"
#define PATH "/d/City/chaos/library/"

string *books, *authors;

create_room()
{
   if(!books)
     books = ({});
  set_short("The Great Library of Arcoron");
  set_long("This is a large room with towering shelves reaching "+
	"from the floor to the ceiling.  The shelves are filled "+
	"with books of all colors, sizes and ages.  Milling about "+
	"the entier library are men in heavy robes, probably the "+
	"librarians.  There is a desk in the north-east corner and "+
	"a doorway leading south into the Great Hall.  Hidden amongst "+
	"the shelves are archways leading north and east.  There is "+
	"a poster near the entrance that says  No Talking!  Further "+
	"down on the poster there are also some instructions. "+
	"Also over the east archway is a small sign.\n");
  add_prop(ROOM_I_LIGHT,1);
  add_prop(ROOM_I_INSIDE,1);
  add_exit(PATH + "hall","south","@@check_for_book",0);
  add_exit(PATH + "domain","east");
  add_exit(PATH + "philosophy","north");
  add_item("sign","This is a small wooden sign with the word Lands printed "+
	"on it.\n");
  add_item("shelves","@@exa_shelves");
  add_item("librarians","These men were hired to keep track of the books "+
	"and texts in the Great Library.  They will probably not let anyone "+
	"leave with books.\n");
  add_item(({"poster","instructions"}),"\n     NO TALKING!\n\n"+
    	"In this library you may look at all the shelves. Some shelves "+
        "are divided into sub-shelves that you also can look at. "+
        "Not all shelves have books yet, but those that contain books "+
	"will show what books they have available. "+
	"Then you can 'read <title>'.\n");
  add_item("books","There are so many of them, you don't know where "+ 
	"to start!\n");
  add_item("desk","The desk isn't, as you would think, covered with "+ 
	"pile upon pile of books, but absolutely clean and tidy. The "+ 
	"reason is that this is no ordinary library where you borrow "+ 
   	"books to take home, but more an archive, a place of lore, "+
	"where records of many a secret thing remain enshrined.  "+
    	"The only reason the librarian is here, is to prevent you from "+
	"leaving with any of the books.\n");

  add_item("arcoron","This shelf is subdivided into smaller groupings. "+
	"Each book is bound in a fine black leather and has it's title "+
	"printed in a dark green ink.  The following books are avaliable:\n"+
	"\n");
  add_item("avenir","Each book on this shelf is bound in a red leather "+
 	"with somewhat worn spines.  The following books are avaliable:\n"+
  	"\n");
  add_item("calia","These books are all bound in a black leather and on the "+
	"cover of each is printed a crystal palace in silver ink.  The "+
	"following books are avaliable:\n"+
	"Argos, Gelan,\n");
  add_item("emerald","The following books are avaliable on Emerald:\n"+
	"Emerald, Faerie, Faerie2,\n");
  add_item("gondor","The following books are avaliable on Gondor: "+
	"Minas_tirith,\n");
  add_item("immortal","The following books on Immortal are avaliable:\n"+
	"\n");
  add_item("kalad","The following books on Kalad are avaliable: "+
	"\n");
  add_item("krynn","The following books on Krynn are avaliable: "+
	"Solace, Neraka, Plains, Huma,\n");
  add_item("liwitch","These books about Liwitch are avaliable: "+
	"\n");
  add_item("rhovanion","The following books are avaliable: "+
	"\n");
  add_item("roke","These books on the Roke area are avaliable:\n"+
	"Re_albi,\n");
  add_item("shire","These books are avaliable: "+
	"\n");
  add_item("terel","These books are avaliable: \n"+
	"S_calathin,\n");
   add_item("misc","This shelf is in a state of total chaos with "+
	"books, scrolls and loose sheet lying about.  It doesn't "+
	"look like anyone has really organized this shelf in a very long "+
	"time.  There are a few books and documents that look potentially "+
	"useful.  They are titled:\n"+
	"Wemic, Behir, Arnds_coat, Dwarven_axe, Sparkle,\n");
}

exa_shelves()
{
  return "The many shelves in the library tower ominously, creating a maze "+
 	"of avaliable knowledge.  Only the plaques on each shelf act as "+
	"guides to thier contents.  Each one is named for a land in "+
	"the world, they are:\n"+
	"Arcoron, Avenir, Calia, Emerald, Gondor, Immortal, Kalad, Krynn, "+
	"Liwitch, Rhovanion, Roke, Shire, Terel, and Misc.\n";
}

check_for_books()
{
  if (present("Arcoron_Library_Book",TP))
    {
write("A robed librarian stops you and says: Please return what you "+
	"have borrowed first.\n");
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
	"look at the librarian. His stern eyes are staring right at you\n"+
	"while he points at the poster which reads 'NO TALKING!'\n"+
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
  if (book == "poster" || book == "instructions") {
    	write("You read the instructions on the poster. "+
    	"In this library you may look at all the shelves. Some shelves "+
    	"are divided into sub-shelves that you also can look at. "+
    	"Not all shelves have books yet, but those that contain books "+
    	"will show what books they have available. "+
	"Then you can 'read <title>'.\n");
    return 1;
    }
  if (book_exists(book))
    {
      write("You read the book titled "+capitalize(book)+".\n");
      say(QCTNAME(TP)+" reads a book from the shelves.\n",TP);
      book = lower_case(book);
      clone_object(MORE_OBJ)->more(DIR+book+".txt", 2);
      return 1;
    }
  write("You don't see that book here.\n");
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
      write("The librarian says: That book is already on our shelves.\n");
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

