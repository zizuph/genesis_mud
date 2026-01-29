 /* Library made by Glinda may -95.
    It inherits Gresolles library from -92.
    A few things have been changed to make it work with a librarian. */
inherit "/d/Avenir/inherit/library";

#include "/d/Avenir/common/bazaar/bazaar.h"
#define LIBR NPC +"librarian"



object librarian;
object quest_npc;


create_library()
{
   my_descs();
   add_book("seafarer","The seafarer. By Snorr E. Lasson.",BOOKS + "book2",1);
   reset();
}

init()
{
   add_action("do_read","read");
   ::init();
}

open_exit()
{
   remove_exit("east");
   add_exit(EXTR + "str2" ,"east");
}

reset_room()
{
   if(!quest_npc)
   {
      if(!random(2))
         quest_npc=clone_object(NPC + "book_man");
      else
         quest_npc=clone_object(NPC + "book_wom");
         quest_npc->arm_me();
      quest_npc->place_me();
   }
   if(!librarian)
   {
      remove_exit("east");
      lib_exit(EXTR + "str2" ,"east");
      librarian=clone_object(LIBR);
      librarian->arm_me();
      librarian->move(TO);
   }
   librarian->set_help(1);
}



borrow(string str)
{
   if(!librarian)
   {
      write("Hmm...Maybe you should wait for the librarian to do that?\n");
   }
   else
   ::borrow(str);
   return 1;
}

return_it(string str)
{
   if(!librarian)
   {
      write("Hmm...Maybe you should wait for the librarian to do that?\n");
   }
   else
   ::return_it(str);
   return 1;
}



do_read(string str)
{
   notify_fail("Read what?");
   if( str == "plaque" || str == "brass plaque")
   {
      write("Please keep quiet!\n");
      return 1;
   }
   if( str == "sign" )
   {
      write("The library offers the following services:\n");
      write("We provide you with a list of the books available.\n");
      write("You may borrow any of these books.\n");
      write("Please have the courtesy to return them before leaving though.\n");
      return 1;
   }
   return 0;
}



void
my_descs()
{
   set_short("Bazaar library");
   set_long(BSN("You are in the library of Bazaar. Huge oaken shelves " +
            "cover the walls from floor, to ceiling. " +
            "The high ceiling along with the stone floor makes every " +
            "sound you make produce a loud echo. To your right is a " +
            "large counter with a discrete brass plaque, and on the wall " +
            "behind the counter is a larger sign. "));
   add_item(({"desk","counter"}),BSN("It is a large walnut desk with a " +
            "small brass sign attached on front of it."));
   add_item(({"plaque","brass plaque"}),BSN("A small brass sign. You can " +
            "probably read it."));
   add_item(({"shelves","shelf","bookshelf","bookshelves"}),BSN("The " +
            "bookshelves contain books."));
   add_item(({"books","book"}),BSN("The books are all sorted in reverse " +
            "alphabetical order."));
   add_item(({"sign"}),BSN("It looks quite informative. Maybe you should " +
            "read it?"));
   add_item(({"floor","stone"}),BSN("The floor is made of dark stone. It " +
            "produces an impressive echo when you walk."));
   add_item(({"ceiling"}),BSN("You tilt your head back and look at the " +
            "ceiling. Pretty uninteresting."));
   add_item(({""}),BSN(""));
   add_item(({""}),BSN(""));
}
