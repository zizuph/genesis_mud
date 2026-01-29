 // 
 // creator(s): Ilyian, September 19, 1995
 // last update:
 // purpose: Book describing one of the demons
 // note:
 // bug(s):
 // to-do:

inherit "/std/book";


#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/SALILUS/"

create_book()
{
   set_short("small tome");
   set_long("This small book feels strangely heavy, "
           +"and has in its cover an image of a lock "
           +"and a key, on a background of a dark "
           +"octagon.\n");
   set_name("tome");
   add_adj("small");
   add_name("avenir_salilus_book");
   set_max_pages(7);

   add_prop(OBJ_I_WEIGHT,673);
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
