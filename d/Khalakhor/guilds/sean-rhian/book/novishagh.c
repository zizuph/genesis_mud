//
// Book - The minor order of the Novishagh; short desc. and vestments
//
// Zima July 2, 1998
//
#include "defs.h"
inherit SR_BOOK_BASE;
 
void create_book()
{
   title="Minor Order of the Novishagh";
   set_short("green cloth-bound book");
   add_name(({"novishagh","Novishagh",title,lower_case(title)}));
   add_adj(({"cloth-bound","green"}));
   set_long("It is a green cloth-bound book entitled: "+title+".\n");
   set_max_pages(2);
   set_book_file("novishagh.txt");
   set_sr_level(0);
}
