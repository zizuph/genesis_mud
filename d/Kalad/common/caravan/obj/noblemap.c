inherit "/std/book";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_book()
{
    set_name("map");
    set_adj("noble");
    add_adj("district");
    set_long("It is a large map of the Noble district in the city of "+
      "Kabal. The map has been placed inside a book to help protect it from "+
      "the rigors of travel.\n");
    set_max_pages(1);
    add_prop(OBJ_I_VALUE,480);
    set_keep();
}
varargs void
read_book_at_page(int which, string verb)
{
    switch(which)
    {
    case 1:
	TP->more("/d/Kalad/open/maps/noble",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
	break;
    }
}
