 // 
 // creator(s): Ilyian, September 19, 1995
 // last update:
 // purpose: Book describing one of the demons
 // note:
 // bug(s):
 // to-do:

inherit "/std/book";


#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/TABRIS/"

create_book()
{
   set_short("strange book");
   set_long("This book is tall and very thin, and "
           +"feels oddly warm. On the cover are "
           +"swirling patterns in dozens of colours.\n");
   set_name("book");
   add_adj("strange");
   add_name("avenir_tabris_book");
   add_item(({"pattern","patterns"}),"The patterns "
           +"seem to move and dance before your eyes.\n");
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
