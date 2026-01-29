#include "../../ctower.h"
 
inherit LIBSTD;

void
create_lib()
{
    object book;
   
    add_exit("glib3", "south");
    add_exit("glib1", "west");
   
    book = clone_object(CTOWER_OBJ + "booke");
    book->move(this_object(), 1);
}
