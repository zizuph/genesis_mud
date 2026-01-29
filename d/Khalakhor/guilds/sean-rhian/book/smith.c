//
// Book - The parable of the Master Smith
//
// Zima July 16, 1998
//
#include "defs.h"
inherit SR_BOOK_BASE;
 
void create_book()
{
   title="Parable of the Master Smith";
   set_short("black leather-bound book");
   add_name(({"parable","smith","master smith", lower_case(title)}));
   add_adj(({"leather-bound","black"}));
   set_long("It is a black leather-bound book entitled: "+title+".\n");
   set_max_pages(3);
   set_sr_level(10);
   set_book_file("smith.txt");
}
