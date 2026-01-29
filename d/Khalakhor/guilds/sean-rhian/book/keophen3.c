//
// Book - Third book of Keophen
//
// Zima July 16, 1998
//
#include "defs.h"
inherit SR_BOOK_BASE;
 
void create_book()
{
   title="The Solsheyderi";
   set_short("black leather-bound book");
   add_name(({"solsheyderi",lower_case(title)}));
   add_adj(({"leather-bound","black"}));
   set_long("It is a black leather-bound book entitled: "+title+".\n");
   set_max_pages(4);
   set_sr_level(20);
   set_book_file("keophen3.txt");
}
