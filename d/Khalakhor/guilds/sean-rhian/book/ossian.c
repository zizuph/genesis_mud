//
// Book - The Revelations To Ossian
//
// Zima May 25, 1998
//
#include "defs.h"
inherit SR_BOOK_BASE;
#include "../defs.h"
 
void create_book()
{
   set_short("black leather-bound book");
   title="Ashlish Ossian";
   add_name(({"ossian",title,lower_case(title)}));
   add_adj(({"leather-bound","black"}));
   set_long("It is a black leather-bound book entitled: "+title+".\n");
   set_max_pages(8);
   set_sr_level(10);
   set_book_file("ossian.txt");
   set_min_lang(15);
}
int allowed(object tp)
{
   if ((::allowed(tp))||(present(SHAM_PENDANT,tp))) return 1;
   return 0;
}
