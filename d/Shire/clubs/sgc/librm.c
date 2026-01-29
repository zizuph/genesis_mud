inherit "/d/Roke/gresolle/open/library";

#include "/d/Shire/sys/defs.h"

#include <stdproperties.h>

create_library()
{
  set_short("Pasting room");
  set_long("This room is supposed to be a library. There are quite "+
           "a few bookshelves, but very few books. The room itself "+
           "looks rarely used to say the least. There are cobwebs "+
           "lurking everywhere. A small librarian, if you could call "+
           "it that, is sleeping in the corner, no doubt tired from "+
           "the strenous work load. On the front of the librarian's "+
           "desk is a sign explaining how to use the library.\n");

   add_item("cobwebs", "They have been left undisturbed for a "+
                "long time.\n");
   add_item("corner", "It looks very musty.\n");
   add_item(({"book","books"}), "Just 'list books' to see what they are.\n");
   add_item(({"bookshelf","bookshelves"}), "They seem to be very under-used.\n");
  add_item("librarian","He is sleeping. You feel you shouldn't "+
           "'wake' him.\n");
  add_item("desk","It is covered with dust.\n");
  add_item("sign", "Yes, you are stupid, but not that stupid.\n");
  add_cmd_item("librarian", "wake", "You foolishly wake the "+
               "goblin, he glares at you hatefully and says: "+
               "Take what you want, and return what you will. "+
               "He then slumps back over and snores loudly.\n");

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


    add_prop(ROOM_I_INSIDE, 1);
    add_prop(ROOM_S_MAP_FILE, "smart_goblin_caves.txt");
   add_prop(OBJ_S_WIZINFO,
"You are standing in a library using the library.c file by Gresolle.\n"+
"It is possible to add books by doing\n"+
"Call here add_book <name>%%<descr>%%<path>%%<type>\n"+
"for more info please check ~gresolle/open/library.c\n"+
"it is also possible to remove books with\n"+
"Call here remove_book <name>. Please don't add anything stupid\n"+
"or offending, and don't remove anything you havn't put there\n"+
"yourself.\n");

   set_save_path(SGC_DIR + "libsave");
   set_lib_name("The Goblin pamphlet room");
   lib_exit(SGC_DIR + "boardrm", "west");

   set_write_dir(SGC_DIR + "books");
   set_librarian_room(SGC_DIR + "bookroom");
}
