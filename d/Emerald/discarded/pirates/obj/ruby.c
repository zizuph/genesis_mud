inherit "/std/object";

#include "defs.h"

void
create_object()
{
   set_short("red ruby");
   set_name("ruby");
   set_adj("red");
   set_long("This ruby is a beautiful deep crimson colour.\n");
   
   add_prop(OBJ_I_VALUE, 75 + random(50));
   add_prop(OBJ_I_WEIGHT,100);
   add_prop(OBJ_I_VOLUME,100);
   
   seteuid(getuid());
}


