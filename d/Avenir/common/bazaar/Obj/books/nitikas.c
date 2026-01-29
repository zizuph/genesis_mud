 // 
 // creator(s): Ilyian, September 19, 1995
 // last update:
 // purpose: Book describing one of the demons
 // note:
 // bug(s):
 // to-do:

inherit "/std/book";


#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/NITIKAS/"

create_book()
{
   set_short("gold covered tome");
   set_long("This elegent book has a thin covering of "
           +"beaten gold around the edges and along the "
           +"sides of the pages. The cover is of light "
           +"brown leather, and on it is a simple "
           +"engraving of a coin.\n");
   set_name("tome");
   add_adj(({"gold","covered"}));
   add_name("avenir_demon_book");
   set_max_pages(7);

   add_prop(OBJ_I_WEIGHT,473);
   add_prop(OBJ_I_VOLUME,580);
   add_prop(OBJ_I_VALUE,875);
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
