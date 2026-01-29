inherit "/d/Roke/gresolle/open/library";

#include "/d/Roke/common/defs.h"
#include "/d/Roke/Cirath/defs.h"
#include <stdproperties.h>

create_library()
{
  set_short("Ciubori Library");
  set_long(break_string(
    "This is the library of Ciubori. The cirathians like to "+
    "entertain themselves with books, thats why the library "+
    "is quite crowdy. Heavy volumes are mixed with more modern "+
    "literature. The whole place is very well-kept. There's a "+
    "sign on the wall, telling how to use the library and a "+
    "librarian stands behind a desk..\n",60));

  add_item("librarian","He doesn't seem to be able to take care of himself.\n");
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
           "                Conan or Vladimir, before they appear in the\n"+
           "                library so it might take a few days before you\n"+
           "                see them after they are written.\n");
  
  add_prop(OBJ_S_WIZINFO,
"You are standing in a library using the library.c file by Gresolle.\n"+
"It is possible to add books by doing\n"+
"Call here add_book <name>%%<descr>%%<path>%%<type>\n"+
"for more info please check ~gresolle/open/library.c\n"+
"it is also possible to remove books with\n"+
"Call here remove_book <name>. Please don't add anything stupid\n"+
"or offending, and don't remove anything you havn't put there\n"+
"yourself.\n");

  set_save_path(CIUBORI+"market/libsave");
  set_lib_name("the Library of Ci'u'bori");
  lib_exit(CIUBORI+"sapphire/street1","west");

  set_write_dir(REDIR+"books");
  set_librarian_room("/d/Roke/conan/workroom");
}
