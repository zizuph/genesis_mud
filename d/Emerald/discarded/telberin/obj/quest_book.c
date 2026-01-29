inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_short("leather bound book");
   set_long("This book is superbly crafted, with a new binding.\n");
   set_name("book");
   add_name("_mylos_quest_book_");
   set_adj("leather");
   add_adj("bound");
   
   add_prop(OBJ_M_NO_BUY, 1);
   add_prop(OBJ_I_WEIGHT, 1443);
   add_prop(OBJ_I_VOLUME, 1245);
}

