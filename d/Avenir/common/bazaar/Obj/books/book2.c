 // Book2          (/d/Avenir/common/bazaar/Obj/books/book1.c)
 // creator(s):    Glinda may -95
 // last update:
 // purpose:       A little something to stick in the library
 //                Maybe a little hint for a quest?
 // note:
 // bug(s):
 // to-do:       rewrite completely to contain antiseafaring propaganda


inherit "/std/book";

#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/B2/"

create_book()
{
   set_long("A black leather book with a red inscription.\n");
   set_name("book");
   set_short("black leather book");
   add_adj(({"black","leather"}));
   add_item(({"inscription"}),"The red letters read: " +
            "The seafarer.\n");
   set_max_pages(7);

   add_prop(OBJ_I_WEIGHT,520);
   add_prop(OBJ_I_VOLUME,680);
   add_prop(OBJ_I_VALUE,495);
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
      case 4:
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
      default:
         cat(BOOKPATH + "blank_page");
   }
   return;
}
