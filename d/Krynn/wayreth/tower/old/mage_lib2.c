/* 
* The library in the tower of Wayreth.
*
* Copy of the library in Vkeep. 
* Changed for the use in Wayreth. 
* Jeremiah, 95/07/26
*/

#include "/d/Krynn/common/defs.h"
#include "/d/Krynn/wayreth/local.h"
#include <macros.h>
#include <composite.h>
#include <cmdparse.h>
#include "mage_lib.h"
inherit TOWERROOM;

#define ENCYCLO "/d/Wiz/tintin/open/encyclopedia.c"

string file; /* The file to look for book. */

void
reset_tower_room()
{
   return;
}


void
create_tower_room()
{
   set_short("Mages library");
   set_long("You find yourself in a library. Lined along the walls " +
      "are shelves with numerous books of different materials, " + 
      "colours and sizes. A treasure of information and " + 
      "knowledge is stored here. This library contains, among " +
      "many others, books with information about the Wizards of " +
      "High Sorcery, a deeper knowledge that cannot be acquired " +
      "elsewhere in the world. Apart from reading here, you can " +
      "also add your own experiences, thoughts or bits of " +
      "information you think would be of interest or value, to " +
      "the collection of books. There are some nice posters " +
      "hanging on the wall here.\n");
   
   add_item(({"poster", "posters"}), "There are three posters here. " +
      "'poster 1' with an index of the books on the shelves, " +
      "'poster 2' with with a list of the newest books in the " +
      "library and 'poster 3' with instructions on how to write " +
      "your own books. Maybe you should read one of them.\n");
   
   add_cmd_item("poster", "read", "@@read");
   
   set_alarm(1.0, 0.0, "reset_tower_room");
   set_wall_type(2);
   
   add_exit(WTOWER + "study", "east", 0);
}


void
init()
{
   ::init();
   ADA("blank");
   ADA("borrow");
   ADD("my_return", "return");
}


int
read()
{
   string rest;
   
   rest = query_item_rest_command();
   if (rest == "3")
      {
      write("To write a new book you should give the command 'blank'. " +
         "Then you can take a blank book from a special shelf. " +
         "This book is yours to fill with whatever you want, maps, " +
         "songs or a novel perhaps. The command to start writing " +
         "can be found examining the blank book. You write a book " +
         "much the same way you write a note on the board. There " +
         "will be private rooms you can enter so others won't " +
         "disturb you if you try to write something. Good luck.\n");
      return 1;
   }
   if (rest == "2")
      {
      write("This is a list of books recently added to the library.\n\n");
      seteuid(getuid(TO));
      cat(NEW_LIST);
      write("\nIf you want to write something, try to 'read poster 3' " +
         "to see how it works.\n");
      return 1;
   }
   
   seteuid(getuid(TO));
   write("This is a list of elder books in the library.\n\n");
   cat(OLD_LIST);
   write("To borrow a book, try 'borrow history'. There is another " +
      "poster with a list of new books. Try 'read poster 2'. " + 
      "If you carry many books you can read the second book with " +
      "the 'read book 2' command. Don't forget to return the books " +
      "before you leave the library.\n");
   
   return 1;
}


int
borrow(string str)
{
   string str2;
   
   str = str + " extra";
   sscanf(str, "%s %s", str2);
   str = str2;
   
   write("You start to search the shelves for a book with the " +
      "title '" + C(str) + "'.\n");
   say(QCTNAME(TP) + " starts to search the shelves, obviously " +
      "looking for a specific book.\n");
   
   set_alarm(5.0, 0.0, "found_book", TP);
   file = L(str);
   return 1;
}

void
found_book(object ob)
{
   string my_file_name, title_name, *adj;
   object book;
   int new, i;
   
   seteuid(getuid(TO));
   
   if (file == ENCYCLO)
      my_file_name = ENCYCLO;
   else
      my_file_name = OLD_BOOKS + file;
   
   if (file_size(my_file_name) < 1)
      {
      my_file_name = NEW_BOOKS + file;
      new = 1;
   }
   
   if (file_size(my_file_name) < 1)
      {
      tell_object(ob, "Searching through all the shelves, you realize " +
         "that there is no such book.\n");
      tell_room(TO, QCTNAME(ob) + " doesn't seem to be able to find " +
         "the book " + PRONOUN(ob) + " was looking for.\n", ob);
      return;
   }
   
   if (my_file_name == ENCYCLO)
      {
      book = clone_object(ENCYCLO);
      book->add_name("lib_book");
   } 
   else 
      {
      book = clone_object(BOOK);
      book->set_file(my_file_name);
      if (new == 0)
         title_name = OLD_LONG + file;
      else
         title_name = NEW_LONG + file;
      book->set_long(read_file(title_name));
      if (new == 0)
         title_name = OLD_SHORT + file;
      else
         title_name = NEW_SHORT + file;
      adj = explode(read_file(title_name), " ") - ({ "book" });
      for (i = sizeof(adj) - 1; i >= 0; i--)
      book->set_adj(adj[i]);
      book->set_short(read_file(title_name));
   }
   
   tell_object(ob, "Searching through the shelves, you find the book " +
      "you were looking for. You take it from its place on " +
      "the shelf.\n");
   tell_room(TO, QCTNAME(ob) + " finds a book and takes it from its " +
      "place on the shelf.\n", ob);
   
   if (book->move(ob))
      {
      book->move(TO);
      tell_object(ob, "You can't carry the book and drop it to the " +
         "ground.\n");
      tell_room(TO, "The book was too heavy and falls to the floor.\n", ob);
   }
}


int
my_return(string str)
{
   object *ob;
   int i;
   
   NF("Return what?\n");
   if (!str)
      return 0;
   
   ob = FIND_STR_IN_OBJECT(str, TP);
   NF("Couldn't find any " + str + " around.\n");
   if (!sizeof(ob))
      return 0;
   
   ob = filter(ob, "lib_books", TO);
   NF("You can only return books from this library.\n");
   if (!sizeof(ob))
      return 0;
   
   write("You return " + COMPOSITE_DEAD(ob) + ".\n");
   say(QCTNAME(TP) + " returns " + QCOMPDEAD + "\n");
   
   for (i = 0; i < sizeof(ob); i++)
   {
      if (ob[i]->id("special_book"))
         write("To bad you didn't choose to bstore it instead.\n");
      
      ob[i]->remove_object();
   }
   
   return 1;
}

int
lib_books(object ob)
{
   return (ob->id("lib_book") || ob->id("special_book") ||
      ob->id("spell_book"));
}

int
blank()
{
   object book;
   
   seteuid(getuid(TO));
   book = clone_object(W_BOOK);
   book->add_name("lib_book");
   say(QCTNAME(TP) + " takes a blank book from one of the shelves.\n");  
   if (book->move(TP) == 0)
      {
      write("You take a brand new blank book from a special shelf.\n");
      return 1;
   }
   say("But it was too heavy. The books falls to the ground.\n");
   write("It's to heavy for you, you drop it.\n");
   book->move(TO);
   return 1;
}

void
leave_inv(object player, object dest)
{
   int took, i;
   object *ob;
   
   ::leave_inv(player, dest);
   
   if (!player || !living(player))
      return;
   
   ob = deep_inventory(player);
   for (i = 0; i < sizeof(ob); i++)
   if (ob[i]->id("lib_book"))
      {
      took++;
      ob[i]->remove_object();
   }
   
   if (took == 1)
      {
      write("A deep voice, sounding from somewhere within your mind, " +
         "reminds you to return the book you borrowed. " +
         "Quickly you put the book back on it's place on the " +
         "shelves, and leave.... a bit ashamed of yourself.\n");   
      
      tell_room(TO, QCTNAME(player) + " forgot to return a book " +
         PRONOUN(player) + " had borrowed from the library. " +
         C(PRONOUN(player)) + " blushes, and quickly returns the " +
         "book to its place on the shelves.\n");
   } 
   else if (took > 1) 
      {
      write("A deep voice, sounding from somewhere within your mind, " +
         "reminds you to return the books you borrowed. " +
         "Quickly you put the books back in their places on the " +
         "shelves, and leave.... a bit ashamed of yourself.\n");
      
      tell_room(TO, QCTNAME(player) + " forgot to return some books " +
         PRONOUN(player) + " had borrowed from the library. " +
         C(PRONOUN(player)) + " blushes, and quickly returns the " +
         "books to their places on the shelves.\n");
   }
   
   if (present("special_book", player))
      write("Please remember to finish writing that book.\n");
}
