 // 
 // creator(s): Ilyian, September 19, 1995
 // last update:
 // purpose: Book describing one of the demons
 // note:
 // bug(s):
 // to-do:

inherit "/std/book";


#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/HAHABI/"

create_book()
{
   set_short("leatherbound book");
   set_long("This is an old book, with worn pages and "
           +"a cracked, soft-leather cover. On the front "
           +"is an sketch of a hand curled into a fist.\n");
   set_name("book");
   add_adj(({"leather-bound","leather","leatherbound"}));
   add_name("avenir_hahabi_book");
   set_max_pages(6);

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
