inherit "/std/book";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_book()
{
   set_name("book");
   set_adj("brown");
   add_adj("spell");
   set_short("brown spell book");
   // Don't get why that is needed, but it did the trick... Rohim
   set_long("A book of richly tanned brown leather, it is riddled with "+
      "many strange runes.\n");
   set_max_pages(1);
   add_prop(OBJ_I_WEIGHT,1000);
   add_prop(OBJ_I_VOLUME,1000);
   add_prop(OBJ_I_VALUE,1000);
}
varargs void
read_book_at_page(int which, string verb)
{
   switch(which)
   {
      case 1:
      write("You try to read and decipher the meanings of the many "+
         "encryptic runes within the spell book but fail utterly.\n");
      break;
   }
}
