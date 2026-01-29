inherit "/std/object";

#include "defs.h"

void
create_object()
{
   set_short("golden chain");
   set_name("chain");
   set_adj("golden");
   set_long("It is an elaborate golden chain. You are unaware of its "+
      "intended use.\n");
   
   add_prop(OBJ_I_VALUE, 1000 + random(500));
   
   
   seteuid(getuid());
}


