inherit "/d/Kalad/common/central/library/library";
#include "/d/Kalad/defs.h"
/* by Antharanos */
create_library()
{
   /* No bell here! Too noisy! */
   INSIDE;
   set_short("The Central District Library of Kabal");
   set_long("You are within a grand rectangular-shaped room whose walls "+
      "are covered with tidy wooden bookshelves that rise all the way to the "+
      "ceiling. The marble floor is covered with a thick red carpet that "+
      "seems to muffle the sounds of your footsteps. At the southern end of the "+
      "room is a desk behind which is the librarian. Many tables also fill this "+
      "room, where visitors to the library may quietly read their books or "+
      "even write them.\n"+
      "A sign stands before you.\n");
   add_item(({"walls","wall"}),"Made from sturdy marble mined from the "+
      "Hespyre mountains, they are prized for their great sound muffling "+
      "abilities, a quality greatly suited for a grand library such as this.\n");
   add_item(({"tidy wooden bookshelves","tidy bookshelves","wooden bookshelves","bookshelves","shelves","bookshelf","shelf"}),
      "They are crafted from solid mahogany and have been polished and "+
      "cleaned to a brilliant shine. Numerous books are lined up along "+
      "them.\n");
   add_item(({"books","book"}),"Wonderful masterpieces written by the "+
      "literary elite.\n");
   add_item(({"ceiling"}),"Also built from marble, several lights "+
      "hang down from it.\n");
   add_item(({"lights","light"}),"They provide illumination for this room.\n");
   add_item(({"marble floor","floor"}),"Very little of it can be seen, "+
      "due to the carpet that covers most of the floor.\n");
   add_item(({"thick red carpet","thick carpet","red carpet","carpet"}),
      "The beautifully woven carpet seems to muffle every footstep made "+
      "in the room.\n");
   add_item(({"desk"}),"A small wooden desk where the librarian does "+
      "his duties.\n");
   add_item(({"librarian"}),"A mousy-looking individual that sits "+
      "quietly behind his desk.\n");
   add_item(({"tables","table"}),"Places where visitors may go to quietly "+
      "read as well as write books.\n");
   add_item(({"sign"}),"There are many words on it, you should read it.\n");
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
   set_save_path("/d/Kalad/common/central/library/libsave");
   set_lib_name("The Central District library of Kabal");
   lib_exit("/d/Kalad/common/central/library/entrance","north",0,-1,-1);
   set_write_dir("/d/Kalad/common/central/library/books");
   set_librarian_room("/d/Kalad/common/central/library/bookroom");
}
