inherit "/std/book";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_book()
{
    set_name("map");
    set_adj("central");
    add_adj("district");
    set_long("It is a large map of the Central district in the city of "+
      "Kabal. The map has been placed inside a book to help protect it from "+
      "the rigors of travel.\n");
    set_max_pages(1);
    add_prop(OBJ_I_VALUE,480);
}
varargs void
read_book_at_page(int which, string verb)
{
    switch(which)
    {
    case 1:
	TP->more("/d/Kalad/open/maps/central",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
	break;
    }
}
