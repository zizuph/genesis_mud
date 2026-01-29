 // 
 // creator(s): Ilyian, September 19, 1995
 // last update:
 // purpose: Book describing one of the demons
 // note:
 // bug(s):
 // to-do:

inherit "/std/book";


#include <stdproperties.h>

#define BOOKPATH "/d/Avenir/common/bazaar/Obj/books/CAHOR/"

create_book()
{
   set_short("dusty blackened tome");
   set_long("This is an old tome, dusty and blackened with "
           +"disuse. It seems the years have been unkind to "
           +"it, or else it has been mistreated, for many "
           +"of the pages seem to be damaged.\nOn the front "
           +"cover of the book is an outline of two eyes "
           +"merging halfway.\n");
   set_name("tome");
   add_adj(({"dusty","blackened"}));
   add_name("avenir_cahor_book");
   add_item(({"image"}),"It makes you feel uncomfortabe to "
           +"look at it for very long, almost as it it were "
           +"looking back at you.\n");
   set_max_pages(9);

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
      case 9:
         cat(BOOKPATH + "p9");
         break;
      default:
         cat(BOOKPATH + "blank_page");
   }
   return;
}
