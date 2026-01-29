inherit "/std/book";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_book()
{
    set_name("map");
    set_adj("detailed");
    add_adj("western");
    add_adj("kalad");
    set_long("A large and detailed map of the western area of the continent of Kalad, which includes "+
      "the city of Kabal and surrounding regions. It has been placed inside a book to help "+
      "protect it from the rigors of travel.\n");
    set_max_pages(1);
    add_prop(OBJ_I_VALUE,840);
    set_keep();
}
varargs void
read_book_at_page(int which, string verb)
{
    switch(which)
    {
    case 1:
	TP->more("/d/Kalad/open/maps/WKalad",1);
	break;
    }
}
