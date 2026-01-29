
inherit "/d/Roke/gresolle/open/library";

#include "/d/Shire/buckland/buckdefs.h"

#include <stdproperties.h>

create_library()
{
    set_short("The library of Brandy Hall.");
    set_long("This is the library of Brandy Hall. There are shelves full "+
      "of books to read covering the walls. The room is large enough that "+
      "there are numerous comfortable chairs to sit in while you browse "+
      "through the books. On one wall is a sign on how to use the library "+
      "because the Master of the Hall got tired of having to answer "+
      "questions and having books taken from him.\n");

    add_item(({"chair","chairs"}),"These chairs look like very comfortable "+
      "places to sit if you plan on doing much reading.\n");

    add_item(({"walls","wall","shelves","shelf"}),"The walls are covered "+
      "completely with shelves containing books on almost everything that "+
      "a hobbit would find interesting.\n");

    add_item(({"book","books"}),"There are many books here. The ones that "+
      "can be borrowed can be seen by doing: list\n");


  add_item("sign", "It has writing which should be read, not "+
                 "merely examined.  As signs go, it is a nice one.\n");
  add_cmd_item("on chair", "sit", "You sit back and relax in one "+
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

   set_save_path(BB_DIR+"libsave");
   set_lib_name("The Library of Brandy Hall");
    lib_exit(BB_DIR + "bh17","north",0,1);

   set_write_dir(BB_DIR+"books");
   set_librarian_room(BB_DIR+"bookroom");




}
