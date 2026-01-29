 // 
 // creator(s): Ilyian, September 19, 1995
 // last update:
 // purpose: Book describing one of the demons
 // note:
 // bug(s):
 // to-do:

inherit "/std/book";


#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/PLALGUS/"

create_book()
{
   set_short("heavy book");
   set_long("This book is very weighty from the rough "
           +"thickness of the pages within. The cover is "
           +"large and has on it a painted blue hammer with "
           +"a lightning bolt going accross it.\n");
   set_name("book");
   add_adj("heavy");
   add_name("avenir_plalgus_book");
   set_max_pages(7);

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
      default:
         cat(BOOKPATH + "blank_page");
   }
   return;
}
