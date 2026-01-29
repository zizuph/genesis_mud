inherit "/std/object";

#include "default.h"

void
create_object()
{
   set_short(0);
   set_long("A brass plaque embedded in the wall.\n");
   set_name("plaque");
   add_name("c_plate");
   
   add_prop(OBJ_I_NO_GET, 1);
   set_no_show();
}

