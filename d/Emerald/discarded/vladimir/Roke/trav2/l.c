inherit "/d/Roke/gresolle/open/library";

#include "/d/Roke/common/defs.h"

#include <stdproperties.h>

create_library()
{
   set_short("Traveller library");
  set_long("This is the Traveller library. In this room many "+
           "stories have been written and told. The room has "+
           "many shelves, some empty, some full. There is an "+
           "old human sitting at a table which you assume to "+
           "be the librarian. Against the wall lies a sign "+
           "explaining how to use the library.\n");

  add_item("librarian","He looks very nervous.\n");
add_item("desk","The desk is used by the librarian to sort returned books.\n");
  add_item("sign",
           "The sign states the procedures for borrowing books:\n"+
           "\nYou must return any previously borrowed books before\n"+
           "you are allowed to borrow any new book, and you are not\n"+
           "allowed to leave the library without returning all books.\n"+
           "\nThe following commands are used:\n"+
           "borrow <book> - borrow a book\n"+
           "return book   - return a book\n"+
           "list          - list all books currently in the library\n\n");
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
    "                Vladimir, before they appear in the library\n"+
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

  set_save_path("/d/Roke/varl/atuan/cape/guild/libsave");
   set_lib_name("The Traveller Library");
  lib_exit("/d/Roke/varl/atuan/cape/guild/balcony", "north");

  set_write_dir("/d/Roke/varl/atuan/cape/guild/books");
  set_librarian_room("/d/Roke/vladimir/workroom");




}
