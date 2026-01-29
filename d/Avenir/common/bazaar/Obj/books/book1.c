 // Book1          (/d/Avenir/common/bazaar/Obj/books/book1.c)
 // creator(s):    Glinda may -95
 // last update:
 // purpose:       A book for a quest..should be returned to the
 //                librarian.
 // note:
 // bug(s):
 // to-do:
 /** Song of the Seeer, Text by Tepisch, Published by Glinda may -95 **/

inherit "/std/book";


#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/B1/"

create_book()
{
   set_long("A small red book with a gold inscription.\n");
   set_name("book");
   add_adj("red");
   set_short("red book");
   add_name("avenir_questbook_id");
   add_item(({"inscription"}),"The golden letters read: " +
            "Song of the seer.\n");
   set_max_pages(8);

   add_prop(OBJ_I_WEIGHT,473);
   add_prop(OBJ_I_VOLUME,580);
   add_prop(OBJ_I_VALUE,595);
   seteuid(getuid());
}

void
read_book_at_page(int which)
{
   switch(which)
   {
     case 1:
         cat(BOOKPATH + "p1");
         break;
      case 2:
         cat(BOOKPATH + "p2");
         break;
      case 3:
         cat(BOOKPATH + "p3");
         break;
      case 4 :
         cat(BOOKPATH + "p4");
         break;
      case 5:
         cat(BOOKPATH + "p5");
         break;
      case 6:
         cat(BOOKPATH + "p6");
         break;
      case 7:
         cat(BOOKPATH + "p7");
         break;
      case 8:
         cat(BOOKPATH + "p8");
         break;
      default:
         cat(BOOKPATH + "blank_page");
   }
   return;
}
