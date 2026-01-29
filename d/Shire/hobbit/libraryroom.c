
#pragma save_binary

inherit "/d/Roke/gresolle/open/library";

#include "/d/Shire/common/defs.h"
#include "hobbit.h"

#include <stdproperties.h>

create_library()
{
  set_short("Adventuresome Hobbits' book room.");
  set_long("Many book shelves dominate this room filled with books. "+
       "A small furry hobbit librarian can just barely be seen "+
           "behind a pile of books on his desk sitting quietly in the "+
           "corner smoking happily away on a pipe. There is a small "+
         "sign just in front of his desk. There are many chairs spread "+
           "about the room for relaxation sake. A narrow doorway "+
           "leads back out to the guild's main hall.\n");

  add_item("librarian","He happily awaits your requests.\n");
  add_item("desk","It is a rather nice hardwood desk.\n");
  add_item("sign", "Maybe you should attempt to use your reading "+
           "skills just a bit?\n");
  add_cmd_item("chair", "sit in", "You sit back and relax in one "+
               "of the most comfortable chairs in the room.\n");

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

   set_save_path(HOBGLD_DIR+"libsave");
   set_lib_name("The Adventuresome Hobbits' Library");
   lib_exit(HOBGLD_DIR + "board","northwest",0,1);
   lib_exit(HOBGLD_DIR + "inn","northeast",0,1);

   set_write_dir(HOBGLD_DIR+"books");
   set_librarian_room(HOBGLD_DIR+"bookroom");




}