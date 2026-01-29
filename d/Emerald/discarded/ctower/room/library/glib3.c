#include "../../ctower.h"
 
inherit LIBSTD;

void
create_lib()
{
    object book;
   
    add_exit("glib2", "north");
    add_exit("glib1", "northwest");
   
    book = clone_object(CTOWER_OBJ + "booki");
    book->move(this_object(), 1);
}
