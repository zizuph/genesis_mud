/* Rohirrim Library in Edoras.
 * This room will contain lots of information for the adventurers.
 * Books of many kinds will be in this room, to read from, not take.
 * Made by Elessar, April/May 1992.
 */

inherit "/std/room";
#include "/sys/stdproperties.h"
#include "/sys/macros.h"
#include "/d/Gondor/elessar/lib/time.h"
#include "/d/Gondor/defs.h"
#define DIR  "/d/Gondor/common/library/books/"
#define BOOK_LIST "/d/Gondor/common/library/books/edbooks"

string *books;

create_room()
{
  set_short("The Library of Rohan in Edoras");
  set_long(BS("You are in a very large hall with shelves along the walls, more shelves on "+
    "the floor, and all the shelves are filled with books of all colours, sizes "+
    "and ages. At a desk in the north-eastern corner of the room stands an aging "+
    "man, probably the Royal Scribe. A doorway leads out to the street east. "+
    "Your gaze stops at a poster by the open door, which says: No talking! "+
    "Further down on the poster you see some instructions. \n"));
  add_prop(ROOM_I_LIGHT,1);
  add_prop(ROOM_I_INSIDE,1);
  add_exit("/d/Gondor/rohan/edoras/path8","east","@@check_for_book",0);
  add_item("shelves","@@exa_shelves");
  add_item("scribe",BS("The Royal Scribe is the person keeping tracks of all the books here "+
	   "in the Library of Edoras. He looks quite old.\n"));
  add_item("poster","\n                 NO TALKING!\n\n"+break_string(
      "Examine the shelves in this library to find which books " +
      "are available. It is not possible to borrow any books, " +
      "but you can of course read any book that is present. \n",45) +
      "Just type 'read <title>'! \n" +
      break_string("If you encounter any problems with this library, " +
      "please put a note onto the board in the Adventurers' " +
      "Guild here in Edoras. \n \n",45) );
  add_item("books","There are so many of them, you don't know where to start!\n");
  add_item("desk",BS("The desk isn't, as you would think, covered with pile upon pile of "+
    "books, but absolutely clean and tidy. The reason is that this is no "+
    "ordinary library where you borrow books to take home, but more an archive, "+
    "a place of lore, where records of many a secret thing remain enshrined. "+
    "One of the reasons that the Scribe is here, is to prevent you from leaving "+
    "with any of the books.\n"));
  add_item("legends","This shelf is parted into several divisions, and a plaque reads:\n"+
	   "'Legends of:\n"+
	   "Lands, Cities, Gods, Heroes, Kings, Artifacts, Enemies, Peoples.\n");
  add_item("lore",BS("The shelf labelled 'Lore' seems to contain books about "+
	   "several subjects of the Nature and life in the wilderness.\n"));
  add_item("history",BS("This shelf is filled with several old books, most of them "+
	   "covered with dust. These are some of the titles you find: ") +
	   "\nAkallabeth1, Akallabeth2.\n");
  add_item("geography",BS("This shelf contains lots of loose papers, probably maps, but "+
	   "also books about places of note in the world.\n"));
  add_item(({"misc","miscellaneous"}),BS("In this shelf there's not much system. You see" +
	   "books and scrolls, loose sheets of paper and great tomes of old.\n"));
  add_item("lands",BS("In the shelf labelled 'Legends of the Lands' you see books about "+
    "special places, lands and kingdoms in the world. ") +
    "\nTitles available: Rohan, Gondor, Anorien, Ithilien, Mordor.\n");
  add_item("cities",BS("This shelf labelled 'Legends of Cities' seems to contain books "+
	   "about different cities.\n"));
  add_item("gods",BS("The shelf labelled 'Legends of the Gods' contains books about "+
	   "the Valar who created Arda, the Earth.\n"));
  add_item("heroes",BS("In the shelf labelled 'Legends of Heroes' you find books about "+
	   "famous people in the history of Middle-Earth.\n"));
  add_item("kings",BS("The shelf labelled 'Legends of Kings' contains books about the "+
	   "Kings of Gondor and other famous kings.\n"));
  add_item("enemies",BS("This shelf labelled 'Legends of the Enemies' contains books "+
	   "about the Enemies of the Free Peoples.\n"));
  add_item("artifacts",BS("In the shelf labelled 'Legends of Artifacts' you see several "+
	   "old books about ancient items and artifacts.\n"));
  add_item("peoples",BS("This shelf, labelled 'Legend of the Peoples' contains books "+
	   "about the different Peoples that live and have lived in the world. ") +
	   "\nYou see these titles: Edain, Rohirrim, Dunedain.\n");
}

exa_shelves()
{
  return BS("There are many shelves, each containing a different sort of books. " +
         "On each shelf is a plaque stating what kind of books it contains. ") +
         "\nThese are the shelves to choose from:\n"+
	     "Legends, Lore, History, Geography, Miscellaneous.\n";
}

check_for_books()
{
  if (present("Edoras_Library_Book",this_player()))
    {
      write("The Royal Scribe stops you, and says: Give me that book first!\n");
      say(QCTNAME(this_player())+" tries to leave with a book, but is stopped.\n",this_player());
      return 1;
    }
  return 0;
}

init()
{
  ::init();
  add_action("no_say","say");
  add_action("no_say","rsay");
  add_action("no_say","shout");
  add_action("no_say","grsay");
  add_action("no_say","laugh");
  add_action("no_say","sing");  
  add_action("read_book","read");
  add_action("add_book","newbook");
  add_action("remove_book","banbook");
  add_action("list_all_books","allbooks");
  add_action("check_time","time");
}

no_say()
{
  write(BS("You are about to open your mouth to speak when you happen to " +
	"look at the Scribe. His stern eyes are staring right at you " +
	"while he is pointing at the poster which reads 'NO TALKING!'\n") +
	"You decide to keep your mouth shut.\n");
  return 1;
}

read_book(string book)
{
  if (!book) {
    write("Read what?\n");
    return 1;
  }
  if(book == "poster")
  {
    write("\n                 NO TALKING!\n\n"+break_string(
      "Examine the shelves in this library to find which books " +
      "are available. It is not possible to borrow any books, " +
      "but you can of course read any book that is present. \n",45) +
      "Just type 'read <title>'! \n" +
      break_string("If you encounter any problems with this library, " +
      "please put a note onto the board in the Adventurers' " +
      "Guild here in Edoras. \n \n",45) );
    return 1;
  }
  if (book_exists(book))
    {
      write("You read the book titled "+capitalize(book)+".\n");
      say(QCTNAME(TP)+" reads a book "+TP->query_pronoun()+" found in the shelves.\n",TP);
      cat(DIR+book+".txt");
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
  book->set_book_title(title);
  book->move(TP);
  return 1;
}

reset_library()
{
  books = ({"Edain","Firstage","Rohirrim","Firstageend","Dunedain"});
  write("The library has been reset.\n");
  save_object(BOOK_LIST);
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
  if (!gondorwiz(TP)) return 0;
  if (book_exists(book)) 
    {
      write("The Royal Scribe says: That book is already in our shelves, dear "+
	TP->query_cap_name()+".\n");
      return 1;
    }
  book = capitalize(lower_case(book));
  books = books + ({book});
  save_object(BOOK_LIST);
  write("You put a book titled "+book+" in the shelves.\n");
  say(QCTNAME(TP)+" puts a new book in the shelves.\n",TP);
  return 1;
}

query_title_list()
{
  string title_list;
  int n;
  restore_object(BOOK_LIST);
  if (!sizeof(books)) return "No books available.\n";
  title_list = "Currently these titles are available in the Royal Library in Edoras: ";
  while (n<sizeof(books)-1)
    {
      title_list = title_list+books[n]+", ";
      n++;
    }
  title_list = title_list+"and "+books[n]+".\n";
  return BS(title_list);
}

list_all_books()
{
  if (!gondorwiz(TP)) return 0;
  write(query_title_list());
  return 1;
}

remove_book(string book)
{
  int n;
  if (!gondorwiz(TP)) return 0;
  if (!book_exists(book))
    {
      write("That book is not in the shelves!\n");
      return 1;
    }
  book = capitalize(lower_case(book));
  restore_object(BOOK_LIST);
  while (n<sizeof(books))
    {
      if (book = books[n]) {
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

gondorwiz(object player)
{
  string name;
  name = capitalize(player->query_real_name());
  if (name == "Elessar" || name == "Hamurabbi" || name == "Olorin"
      || name == "Tricky" || name == "Randor" || name == "Costa"
      || name == "Zephram") return 1;
  return 0;
}
