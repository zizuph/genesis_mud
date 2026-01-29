#include "../../ctower.h"

inherit LIBSTD;

void
create_lib()
{
    object book;
   
    add_exit("blib3", "southwest");
    add_exit(CTOWER_ROOM + "hall2", "north");
    add_exit("blib2", "west");
  
    book = clone_object(CTOWER_OBJ + "bookc");
    book->move(this_object(), 1);
}
