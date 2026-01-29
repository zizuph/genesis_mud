//
// Book - The Vestments of the Order, pictures and regulations
//
// Zima June 25, 1998
//
#include "defs.h"
inherit SR_BOOK_BASE;
 
void create_book()
{
   title="Vestments of Sean-Rhian";
   set_short("green cloth-bound book");
   add_name(({"vestments","Vestments",title,lower_case(title)}));
   add_adj(({"cloth-bound","green"}));
   set_long("It is a green cloth-bound book entitled: "+title+".\n");
   set_max_pages(15);
   set_book_file("vests.txt");
}
