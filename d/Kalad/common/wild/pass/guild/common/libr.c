 inherit "/d/Roke/gresolle/open/library";
#include "/d/Kalad/defs.h"
#include <stdproperties.h>
create_library()
{
  set_short("A quiet room.");
  set_long("You have entered a small alcove in the entrance hall of "
	+"the famous Drow Academy. To the west lies the room where "
	+"certain people are given the honour of entering the ranks "
	+"of the Drow Academy. Contained in this alcove is a small "
	+"library used by members and non-members to share stories "
	+"and explain the religion of Lloth. Silence is essential "
	+"here, make not a noise, lest you be driven out by the wrath "
	+"of Lloth. There is a small sign posted explaining the way "
	+"the library works in the corner.\n");
  add_item("sign", "Maybe you should attempt to use your reading "+
           "skills just a bit?\n");
  add_item(({"alcove"}),"This is a small alcove where the library is.\n");
  add_cmd_item("satan", "worship", "You fool!! God is way cooler!! "+
               "Who do you think he banished Lucifer from heaven???  "+
               "He let a bitchin' babe like Eve walk around buck "+
               "naked!! Get a grip!!\n");
  add_cmd_item("sign","read",
   "The sign states the procedures for borrowing books:\n"+
   "\nYou must return any previously borrowed books before\n"+
   "you are allowed to borrow any new book, and you are not\n"+
   "allowed to leave the library without returning all books.\n"+
   "\nThe following commands are used:\n"+
   "borrow <book> - borrow a book\n"+
   "return book   - return a book\n"+
   "list          - list all books currently in the library\n\n"+
   "write book    - write a book and submit it to the library.\n"+
   "                all written books has to be accepted by\n"+
   "                an immortal, before they appear in the library\n"+
   "                so it might take a few days before you see\n"+
   "                them after they are written.\n");
   add_prop(OBJ_S_WIZINFO,
"You are standing in a library using the library.c file by Gresolle.\n"+
"It is possible to add books by doing\n"+
"Call here add_book <name>%%<descr>%%<path>%%<type>\n"+
"for more info please check ~gresolle/open/library.c\n"+
"it is also possible to remove books with\n"+
"Call here remove_book <name>. Please don't add anything stupid\n"+
"or offending, and don't remove anything you havn't put there\n"+
"yourself.\n");
   set_save_path("/d/Kalad/common/wild/pass/guild/common/libsave");
   set_lib_name("A quiet library");
   lib_exit("/d/Kalad/common/wild/pass/guild/common/joinroom", "west");
   set_write_dir("/d/Kalad/common/wild/pass/guild/common/books");
   set_librarian_room("/d/Kalad/common/wild/pass/guild/common/bookroom");
}
