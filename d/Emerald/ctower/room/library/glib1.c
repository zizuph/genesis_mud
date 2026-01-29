#include "../../ctower.h"
 
inherit LIBSTD;

void
create_lib()
{
    object book;
   
    add_exit("glib3", "southeast");
    add_exit(CTOWER_ROOM_ENTRY + "hall4", "north");
    add_exit("glib2", "east");
  
    book = clone_object(CTOWER_OBJ + "bookq");
    book->move(this_object(), 1);
  
    book = clone_object(CTOWER_OBJ + "bookm");
    book->move(this_object(), 1);
}
