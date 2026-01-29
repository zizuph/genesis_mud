//
// Book - The Presbytairs; general info on leaders of the order
//
// Zima July 2, 1998
//
#include "defs.h"
inherit SR_BOOK_BASE;
 
void create_book()
{
   title="Presbytairs of Sean-Rhian";
   set_short("green cloth-bound book");
   add_name(({"presbytairs","Presbytairs",title,lower_case(title)}));
   add_adj(({"cloth-bound","green"}));
   set_long("It is a green cloth-bound book entitled: "+title+".\n");
   set_max_pages(3);
   set_book_file("presbytair.txt");
   set_sr_level(0);
}
