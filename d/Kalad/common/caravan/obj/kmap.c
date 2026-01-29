inherit "/std/book";
inherit "/lib/keep";
#include "/d/Kalad/defs.h"
/* by Antharanos */
void
create_book()
{
    set_name("map");
    set_adj(({"kabal","city"}));
    set_short("kabal city map");
    set_long("A large map of the city of Kabal. It has been placed inside "+
      "a book to help protect it from the rigors of travel.\n");
    set_max_pages(1);
    add_prop(OBJ_I_VALUE,360);
    set_keep();
}
varargs void
read_book_at_page(int which, string verb)
{
    switch(which)
    {
    case 1:
	TP->more("/d/Kalad/open/maps/Kabal",1,(int)TP->query_prop(PLAYER_I_MORE_LEN));
	break;
    }
}
