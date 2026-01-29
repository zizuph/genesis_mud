
#pragma save_binary

inherit "/d/Roke/gresolle/open/library";

#include "/d/Shire/common/defs.h"
#include "heren_istimor.h"

#include <stdproperties.h>

create_library()
{
 set_short("A place of learning and scholarship");
  set_long("Here, among the branches, in the many nooks and crannies "+
                 "naturally made by the tree is a place where many scrolls "+
                 "and small books are kept.  A leather cover covers those "+
                "places where rain is apt to seep in, but on the whole the "+
                "scrolls are left to the open air, as copies are constantly being "+
               "made by junior Heralds.  The main tree branch that led here, also "+
     "ends here.  A sign posted to the tree will "+
     "give further information.\n");

   add_item(({"branches","nooks","crannies","nook","cranny"}),
   "The branches twisting upward and every which way make many "+
   "convenient cubby-holes for putting scrolls and small books.\n");

    add_item(({"scroll","scrolls","book","small book","books"}),
    "The scrolls and books can be listed by doing: list.\n");

    add_item(({"leather cover","cover","covers","leather covers"}),
    "The leather covers protect from direct sunlight as well as "+
    "water damage.\n");

   add_item(({"branch","tree branch","main tree branch"}),
   "The strong main tree branch that leads to the main trunk "+
   "goes southeast of here back to a meeting of the ways.\n");

  add_item("sign", "It has writing which should be read, not "+
                 "merely examined.  As signs go, it is a nice one.\n");
  add_cmd_item("branch", "sit on", "You sit back and relax in one "+
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

   set_save_path(HEREN_ISTIMOR_DIR+"libsave");
   set_lib_name("The Library of the Heren Istimor");
   lib_exit(HEREN_ISTIMOR_DIR + "board","southwest",0,1);

   set_write_dir(HEREN_ISTIMOR_DIR+"books");
   set_librarian_room(HEREN_ISTIMOR_DIR+"bookroom");




}
